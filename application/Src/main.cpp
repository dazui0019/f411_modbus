#include "gpio.h"
#include "main.h"
#include "usart.h"
#include "tim.h"
#include "led.h"
#include "bsp_usart.h"
#include "modbus.h"
#include "hicode.h"
#include "retarget.h"
#include "timer.h"
#include "frame.h"

//标志位
extern uint8_t debug_recFlag;
extern uint8_t modbus_recFlag;
extern uint8_t esp_recFlag;
//缓冲区
extern uint8_t mb_rec_Buffer[MB_RecLength];    //modbus接收缓冲
extern uint8_t frame_Buffer[FrameLength];     //debug(frame)接收缓冲

extern uint8_t isTime;      //定时器触发标志
int main()
{
    //调用初始化函数
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    MX_USART1_UART_Init();  //usart1用于modbus通信
    MX_USART2_UART_Init();  //板载stlink 接的是（PA2, PA3），也就是USART2.用来debug
    MX_USART6_UART_Init();  //usart3和esp32通信
    RetargetInit(&DEBUG_SER);  //printf重定向

    HAL_UART_Receive_IT(&MODBUS_SER, mb_rec_Buffer, MB_RecLength);  //使能串口中断接收
    HAL_UART_Receive_IT(&FRAME_SER, frame_Buffer, FrameLength);    //使能串口中断接收

    MX_TIM10_Init(); //初始化定时器
    HAL_TIM_Base_Start_IT(&MODBUS_TIMER);   //启动定时器（中断）

    led blue(GPIOC, GPIO_PIN_13);
    blue.off();
    //传感器对象
    sensor soil(0x01);

    frame esp(frame_Buffer, blue);    //用来和esp32通信
    modbus modbus(mb_rec_Buffer);   //modbus对象
    soil.structure_traMsg();    //构建发送报文
    BON_INFO("test: ");
    while(1){
        //串口接收完毕
        if((esp_recFlag || debug_recFlag || modbus_recFlag) == SET){
            if(modbus_recFlag){
                modbus_recFlag = RESET;
                if(modbus.Modbus_ReceiveHandler(soil) == MODBUS_OK){
                    esp.send_data(soil);
                    BON_DEBUG("moisture: %d, temperature: %.1f", soil.moisture, soil.temperature);
                }
            }else if(esp_recFlag){
                esp_recFlag = RESET;
                BON_DEBUG("frame rec");
                esp.Frame_Handler(soil);
            }else if(debug_recFlag){
                debug_recFlag = RESET;
                //debug口主要是发送调试信息，所以没有开启接收中断。
            }
        }
        if(isTime) {
            isTime = RESET;
            modbus::Modbus_Transmit(soil);
//            blue.toggle();
        }
    }
    return 0;
}
