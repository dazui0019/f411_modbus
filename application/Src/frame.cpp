/**
 * maximum size: 4 byte
 * start byte: 0xAA
 * device ID:
 * function code:
 * stop byte: 0x55
 *
 * e.g. 0xAA 0x4C 0x4F 0x55
 */
#include "gpio.h"
#include "frame.h"
#include "usart.h"
#include "retarget.h"
#include "bsp_usart.h"

//处理帧头、帧尾以及设备码
void frame::Frame_Handler(sensor& sensor){
    if(recBuffer[0] == 0xAA && recBuffer[3] == 0x55){
        switch(recBuffer[1]){ //检查 device id
            case 0x53:
                frame::from_esp32(recBuffer[2], sensor);
                break;
            case 0x4C:
                Device_led(recBuffer[2]);
                break;
            default:
                BON_DEBUG("device code error!");
                break;
        }
    }else {
        BON_DEBUG("head code error!");
        BON_DEBUG("%x", recBuffer[0]);
    }
}

/**
 * device ID: 0x53
 * function code: 0x55（获取数据）、0x57()
 */
void frame::from_esp32(uint8_t function, sensor& sensor){
    switch (function) {
        case 0x55:
            BON_DEBUG("upload data!");
            send_data(sensor);
            break;
        case 0x57:
            //todo
            break;
        default:
            BON_DEBUG("function code error!");
            break;
    }
}

void frame::send_data(sensor& sensor){
    sprintf((char*)traBuffer, R"({"sensor":["soil"],"soilValue":[%d, %.1f]})", sensor.moisture, sensor.temperature);
    HAL_UART_Transmit(&FRAME_SER, traBuffer, sizeof(traBuffer), 10);
    BON_DEBUG(R"({"sensor":["soil"],"soilValue":[%d, %.1f]})", sensor.moisture, sensor.temperature);
}

/**
 * device ID: 0x4C
 * function code: 0x4F（开灯）， 0x46（关灯）
 */
void frame::Device_led(uint8_t function){
    switch (function) {
        case 0x46:
            frameLed.off();
            BON_DEBUG("led turn off");
            break;
        case 0x4F:
            frameLed.on();
            BON_DEBUG("led turn on");
            break;
        default:
            BON_DEBUG("function code error!");
            break;
    }
}
