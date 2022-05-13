#ifndef FRAME_H
#define FRAME_H

#include "hicode.h"
#include "main.h"
#include "gpio.h"
#include "led.h"

class frame{
public:
    explicit frame(uint8_t Buffer[], led& frameLed): frameLed(frameLed){   //构造函数需要指定缓冲区。
        frameLed.on();
        recBuffer = Buffer;
    }
    void Frame_Handler(sensor& sensor);
    void Device_led(uint8_t function);
    void from_esp32(uint8_t function, sensor& sensor);
    void send_data(sensor& sensor);
    uint8_t* recBuffer;
    uint8_t traBuffer[40] = {0};
    led frameLed;
};

#endif
