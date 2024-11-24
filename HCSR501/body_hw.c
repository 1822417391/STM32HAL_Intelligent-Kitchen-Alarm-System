#include "body_hw.h"

uint16_t value = 0;

uint8_t HUMAN_t = 0;

void BODY_HW_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 打开GPIO时钟
    __HAL_RCC_GPIOB_CLK_ENABLE(); // 将BODY_HW_GPIO_CLK替换为具体的GPIO时钟宏，示例使用GPIOB

    // 配置GPIO引脚
    GPIO_InitStructure.Pin = BODY_HW_GPIO_PIN;          // GPIO引脚
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;          // 输入模式
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;            // 下拉模式

    HAL_GPIO_Init(BODY_HW_GPIO_PORT, &GPIO_InitStructure); // 初始化GPIO
}

uint16_t BODY_HW_GetData(void)
{
    uint16_t People_Data;
    People_Data = HAL_GPIO_ReadPin(BODY_HW_GPIO_PORT, BODY_HW_GPIO_PIN);
    return People_Data;
}

void HCSR501_proc(void)
{
    if (HUMAN_t % 10 == 0) /* 每100ms读取一次 */
        {
            value = BODY_HW_GetData();             
        }

        delay_ms(10);
        HUMAN_t++;
}

