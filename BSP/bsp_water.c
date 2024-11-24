#include "bsp_water.h"

// ��������źŶ���
#define SERVO_STOP      150  // ֹͣ�ź� (1.5ms)
#define SERVO_FORWARD   170  // ˳ʱ����ת�ź� (1.7ms)
#define SERVO_REVERSE   130  // ��ʱ����ת�ź� (1.3ms)

static uint8_t temp = 0;

void water_proc() {
    // ��ȡPB9���ŵ�ƽ
    GPIO_PinState pb9_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
    
    if (pb9_state == GPIO_PIN_RESET && temp == 0) { // PB9�͵�ƽ
        // ˳ʱ����ת
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, SERVO_FORWARD);
        delay_ms(300);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, SERVO_STOP);
        temp = 1;
    } else if (pb9_state == GPIO_PIN_SET) { // PB9�ߵ�ƽ
        // ֹͣ���
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, SERVO_STOP);
        temp = 0;
    }
}
