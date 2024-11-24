#include "body_hw.h"

uint16_t value = 0;

uint8_t HUMAN_t = 0;

void BODY_HW_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // ��GPIOʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE(); // ��BODY_HW_GPIO_CLK�滻Ϊ�����GPIOʱ�Ӻ꣬ʾ��ʹ��GPIOB

    // ����GPIO����
    GPIO_InitStructure.Pin = BODY_HW_GPIO_PIN;          // GPIO����
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;          // ����ģʽ
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;            // ����ģʽ

    HAL_GPIO_Init(BODY_HW_GPIO_PORT, &GPIO_InitStructure); // ��ʼ��GPIO
}

uint16_t BODY_HW_GetData(void)
{
    uint16_t People_Data;
    People_Data = HAL_GPIO_ReadPin(BODY_HW_GPIO_PORT, BODY_HW_GPIO_PIN);
    return People_Data;
}

void HCSR501_proc(void)
{
    if (HUMAN_t % 10 == 0) /* ÿ100ms��ȡһ�� */
        {
            value = BODY_HW_GetData();             
        }

        delay_ms(10);
        HUMAN_t++;
}

