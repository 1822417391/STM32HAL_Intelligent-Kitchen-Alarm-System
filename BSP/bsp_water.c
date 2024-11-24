#include "bsp_water.h"

// 舵机控制信号定义
#define SERVO_STOP      150  // 停止信号 (1.5ms)
#define SERVO_FORWARD   170  // 顺时针旋转信号 (1.7ms)
#define SERVO_REVERSE   130  // 逆时针旋转信号 (1.3ms)

static uint8_t temp = 0;

void water_proc() {
    // 读取PB9引脚电平
    GPIO_PinState pb9_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
    
    if (pb9_state == GPIO_PIN_RESET && temp == 0) { // PB9低电平
        // 顺时针旋转
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, SERVO_FORWARD);
        delay_ms(300);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, SERVO_STOP);
        temp = 1;
    } else if (pb9_state == GPIO_PIN_SET) { // PB9高电平
        // 停止舵机
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, SERVO_STOP);
        temp = 0;
    }
}
