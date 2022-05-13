#include "tim.h"
#include "timer.h"

uint8_t isTime = RESET;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance == MODBUS_TIMER_BASE){
        isTime = SET;
    }
}