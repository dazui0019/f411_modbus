#ifndef F4_LED_H
#define F4_LED_H

class led{
    public:
        led() = default;
        led(GPIO_TypeDef* GPIOx, uint16_t Pin){
            pin = Pin;
            gpio = GPIOx;
        }
        void blink();   //闪烁led
        void toggle();
        void on();  //点亮led
        void off(); //熄灭led
        void setDelay(uint32_t Delay);  //设置闪烁间隔
        void revLevel();    //反转引脚电平, 有些开发板是高电平点亮。

    private:
        GPIO_TypeDef* gpio = GPIOC;
        uint16_t pin = GPIO_PIN_13;
        uint32_t delay = 1000;
        GPIO_PinState openState = GPIO_PIN_RESET;
        GPIO_PinState closeState = GPIO_PIN_SET;
};

#endif