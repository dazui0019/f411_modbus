#include "gpio.h"
#include "led.h"

void led::blink(){
    HAL_GPIO_TogglePin(gpio, pin);
    HAL_Delay(delay);
}
void led::setDelay(uint32_t Delay) {
    delay = Delay;
}

void led::on(){
    HAL_GPIO_WritePin(gpio, pin, openState);
}

void led::off(){
    HAL_GPIO_WritePin(gpio, pin, closeState);
}

void led::toggle() {
    HAL_GPIO_TogglePin(gpio, pin);
}

//改为高电平点亮
void led::revLevel(){
    openState = GPIO_PIN_SET;
    closeState = GPIO_PIN_RESET;
}
