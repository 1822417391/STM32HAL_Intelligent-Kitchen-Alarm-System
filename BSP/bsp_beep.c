#include "bsp_beep.h"

volatile uint16_t BEEP_state = 1;    //蜂鸣器标志位，1不叫，0叫

void warning_proc(void)
{
    // 读取PB9引脚电平
    GPIO_PinState pb9_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
    uint16_t smoke_level = adc_value;
    
    //火焰判断
    if(temperature > 60)
    {
        BEEP_state = 0;
        return;
    }
    
    //烟雾判断
    if(smoke_level > MQ2_THRESHOLD)
    {
        BEEP_state = 0;
        return;
    }
    
    //溢水判断
    if (pb9_state == GPIO_PIN_SET)
    {
        BEEP_state = 0;
        return;
    }
    
    //如果都没触发就关闭蜂鸣器
    BEEP_state = 1;
}

void beep_proc(void)
{
    if (BEEP_state == 0)
    {
        // BEEP_state == 0 时，输出低电平触发蜂鸣器
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);  // 设置 PB4 为低电平

    }
    else
    {
        // BEEP_state == 1 时，输出高电平关闭蜂鸣器
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);    // 设置 PB4 为高电平

    }
}
