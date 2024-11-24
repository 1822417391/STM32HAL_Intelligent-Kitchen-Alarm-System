#include "bsp_led_ui.h"
/* 引脚提醒：LED1- PA9 LED2- PA10 LED3- PA11 LED4- PA12*/
/*  */

/* LED界面灯的4个状态 */
/* LED_UI[0] -> PA9的状态，LED_UI[1] -> PA10的状态，....以此类推*/
uint8_t LED_UI[4] = {1,0,0,0};  //初始化只有界面1亮

void led_ui_disp(uint8_t *LED_UI)
{
    // 用于记录当前 LED 状态的临时变量
    uint8_t temp = 0x00;
    // 使用静态变量，记录之前 LED 状态的变量，用于判断是否需要更新显示
    static uint8_t temp_before = 0xff;  // 初始化为 0，避免第一次进入函数就跳过更新

    // 只处理 LED_UI 数组的前4个元素，对应 PA9-PA12
    for (int i = 0; i < 4; i++) 
    {
        // 将当前元素的值根据索引设置到 temp 变量的对应位
        if (LED_UI[i]) 
            { // 如果 LED_UI[i] 为真 (非零)
            temp |= (1 << i); // 设置 temp 的对应位为 1
            } 
        else 
            { // 如果 ucLed[i] 为假 (零)
            temp &= ~(1 << i); // 设置 temp 的对应位为 0
            }
    }

    // 仅当当前状态与之前状态不同的时候，才更新显示
    if (temp != temp_before) 
    {
        // 使用 BSRR 寄存器更高效地设置和清除引脚
        // 先清除所有相关的引脚
        GPIOA->BSRR = (0x0F << (9 + 16));  // 将 PA9-PA12 置低，+16 是为了访问 BSRR 的低 16 位 (BRR)

        // 再设置需要置低的引脚
        GPIOA->BSRR = ((~temp & 0x0F) << 9);         // 根据 temp 的值设置 PA9-PA12


        temp_before = temp;    // 更新记录的旧状态
    }


}

/* 函数名称：led_ui_proc() */
/* 函数作用：LED 显示处理函数 */
/*           每次调用led_ui_proc()时，LED 根据 LED_UI 数组中的值来决定开启还是关闭 */
void led_ui_proc(void)
{

    //根据OLED显示逻辑写判断逻辑
    LED_UI[0] = (oled_disp_mode == 0);
    LED_UI[1] = (oled_disp_mode == 1);
    LED_UI[2] = (oled_disp_mode == 2);
    LED_UI[3] = (oled_disp_mode == 3);
    
    //显示当前 Led_Pos 位置的 LED 灯状态
    led_ui_disp(LED_UI);
}
