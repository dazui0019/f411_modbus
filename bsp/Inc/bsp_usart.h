#ifndef BSP_USART_H
#define BSP_USART_H

//MODBUS口
#define MODBUS_SER huart1
#define MODBUS_SER_BASE USART1

//DEBUG口
#define DEBUG_SER huart2
#define DEBUG_SER_BASE USART2

//单片机之间通信
#define FRAME_SER huart6
#define FRAME_SER_BASE USART6

#define MB_RecLength 9
#define FrameLength 4

void HAL_UART_IdleCallback(UART_HandleTypeDef *huart);

#endif