#include "main.h"
#include "usart.h"
#include "bsp_usart.h"
#include "retarget.h"

uint8_t debug_recFlag = RESET;  //接收完成标志位
uint8_t modbus_recFlag = RESET; //接收完成标志位
uint8_t esp_recFlag = RESET;    //接收完成标志位

uint8_t mb_rec_Buffer[MB_RecLength];    //modbus接收缓冲
uint8_t frame_Buffer[FrameLength];     //debug接收缓冲

//接收完毕中断回调函数,Cplt指的应该是complete。
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//    USART2只是一个地址（寄存器基地址），而huarx是一个HAL库中的结构体，存储了很多信息，其中就包括了寄存器基地址（USARTx）。
    if(huart->Instance == MODBUS_SER_BASE){
        modbus_recFlag = SET;
        HAL_UART_Receive_IT(&MODBUS_SER, mb_rec_Buffer, MB_RecLength);
    }else if(huart->Instance == FRAME_SER_BASE){
        esp_recFlag = SET;
        HAL_UART_Receive_IT(&FRAME_SER, frame_Buffer, FrameLength); //重新使能中断接收
    }
}

//空闲中断回调
void HAL_UART_IdleCallback(UART_HandleTypeDef *huart){
    if(huart->Instance == DEBUG_SER_BASE){
        debug_recFlag = SET;
    }
}
