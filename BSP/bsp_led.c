#include "bsp_led.h"
/* 引脚提醒：LED_YEL- PB13 LED_GRN- PB14 LED_RED- PB15*/
/*  */

/* LED提示灯的3个状态 */
/* LED状态：常态黄灯YEL常亮，有人GRN亮，警报RED亮 */
uint8_t LED_TIP[3] = {0,0,0};  //初始化黄灯常亮

void led_disp(uint8_t *LED_TIP)
    {
    // 用于记录当前 LED 状态的临时变量
    uint8_t temp = 0x00;
    // 使用静态变量，记录之前 LED 状态的变量，用于判断是否需要更新显示
    static uint8_t temp_before = 0xff;  // 初始化为 0，避免第一次进入函数就跳过更新

    // 只处理 LED_TIP 数组的前3个元素，对应 PB13-PB15
    for (int i = 0; i < 3; i++)
        {
        // 将当前元素的值根据索引设置到 temp 变量的对应位
        if (LED_TIP[i] != 0) 
            { // 如果 LED_TIP[i] 为真 (非零)
            temp |= (1 << i); // 设置 temp 的对应位为 1
            } 
            else 
            { // 如果 LED_TIP[i] 为假 (零)
            temp &= ~(1 << i); // 设置 temp 的对应位为 0
            }
        }

    // 仅当当前状态与之前状态不同的时候，才更新显示
    if (temp != temp_before) 
        {
            if (temp & (1 << 0))
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
            }

            if (temp & (1 << 1))
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
            }

            if (temp & (1 << 2))
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
            }
            else
            {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
            }

            temp_before = temp;    // 更新记录的旧状态
        }
}
    
/* 函数名称：led_proc() */
/* 函数作用：LED 显示处理函数 */
/*           每次调用led_proc()时，LED 根据 LED_TIP 数组中的值来决定开启还是关闭 */
void led_proc(void)
{
    // 重置所有 LED 状态为关闭
    LED_TIP[0] = 1;  // 黄灯
    LED_TIP[1] = 1;  // 绿灯
    LED_TIP[2] = 1;  // 红灯   
    
    // 根据当前状态设置 LED 状态
    if (currentStatus == NO_PERSON) {
        LED_TIP[0] = 0;  // 无人状态，黄灯亮
    }
    else if (currentStatus == PERSON_PRESENT) {
        LED_TIP[1] = 0;  // 有人状态，绿灯亮
    }
    if(BEEP_state == 1)
    {
        LED_TIP[2] = 0;  
    }
    else
    {
        LED_TIP[2] = 1;  // 警报状态，红灯亮
    }
    //显示当前 Led_Pos 位置的 LED 灯状态
    led_disp(LED_TIP);

    
}
