#include "bsp_oled.h"


HumanStatus currentStatus = NO_PERSON;

/* 文件名称：bsp_oled.c */
/* 文件作用：格式化字符串并显示在指定的 OLED 行上  */

/* 
 *
 * 参数说明：
 * Line      要显示字符串的 OLED 行号
 * format    格式化字符串，后跟要格式化的字符串
 *
 * 变量声明：
 * vsprintf  格式化字符串，调用'OLED_DisplayStringLine' 显示格式化后的字符串
 *
 * 示例用法：
 * OLEDSprintf(1, 1, "Hello, world!");  // 在第一行第一列显示 "Hello, world!"
 * OLEDSprintf(2, 1, "Counter: %d", counter); // 在第二行第一列显示计数器值
 * OLEDSprintf(3, 1, "Float: %.2f", 3.14159);  // 在第三行第一列显示浮点数，保留两位小数
 *
 */
void OLEDSprintf(uint8_t Line, uint8_t Column, const char *format, ...)
{
    char String[17]; // 增加缓冲区大小，以容纳更长的字符串，OLED的屏宽为16
    va_list arg;
    va_start(arg, format);
    vsnprintf(String, sizeof(String), format, arg); // 使用 vsnprintf 避免缓冲区溢出
    va_end(arg);    //清理参数列表
    OLED_ShowString(Line, Column, String);  // 显示字符串到OLED
}

uint8_t oled_disp_mode = 0 ;// 显示OLED模式, = 0温湿度检测界面/ = 1溢水检测界面/ = 2烟雾检测界面/ = 3人体存在检测界面

void oled_proc(void)
{
    // 读取PB9引脚电平
    GPIO_PinState pb9_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
    
    switch(oled_disp_mode)
    {
        // DHT11温度检测界面
        case 0:            
            OLEDSprintf(1, 6, "DHT11");
            OLEDSprintf(2, 1, "Temp: %dC        ", temperature);
            OLEDSprintf(3, 1, "Humi: %d%%Rh     ", humidity);
            if(temperature > 60)
            {
                OLED_ShowString(4, 1, "WARNING!    ");
            }
            else{
                OLED_ShowString(4, 1, "SAFE         ");
            }
            break;

        // 溢水检测界面
        case 1:
            OLED_ShowString(1, 6, "WATER");
        
             if (pb9_state == GPIO_PIN_RESET) // 低电平
            { 
                // 溢水提示
                OLED_ShowString(2,1,"WATER <HIGH>   ");
                OLED_ShowString(3, 1, "WARNING!    ");
                
            }
            else if (pb9_state == GPIO_PIN_SET) // 高电平
            { 
                // 没溢水提示
                OLED_ShowString(2,1,"WATER <LOW>    ");
                OLED_ShowString(3, 1, "SAFE         ");
            } 
            OLED_ShowString(4, 1, "             ");
            break;

        // 烟雾检测界面
        case 2:
            OLED_ShowString(1, 6, "SMOKE");
                // 打印信息并判断阈值
            OLEDSprintf(2,1,"Value: %d     ", adc_value);
            if(adc_value <= MQ2_THRESHOLD)
            {
                OLED_ShowString(3, 1, "SAFE         ");
            }
            else
            {
                OLED_ShowString(3, 1, "WARNING!    ");
            }
            OLED_ShowString(4, 1, "             ");
            break;

        // 人体存在检测界面
        case 3:
            OLED_ShowString(1, 6, "HUMAN");
            OLED_ShowString(2, 1, "HAVE ANYONE?");

            switch (currentStatus)
            {
                case NO_PERSON:
                    if (value == GPIO_PIN_SET) 
                    {
                        // 检测到有人的信号，切换到有人的状态
                        currentStatus = PERSON_PRESENT;
                        OLED_ShowString(3, 1, "HAVE SOMEONE");

                    } 
                    else 
                    {
                        OLED_ShowString(3, 1, "NOBODY          ");

                    }
                    break;

                case PERSON_PRESENT:
                    if (value == GPIO_PIN_RESET) 
                    {
                        // 检测到没有人的信号，切换到没有人的状态
                        currentStatus = NO_PERSON;
                        OLED_ShowString(3, 1, "NOBODY          ");

                    } 
                    else 
                    {
                        OLED_ShowString(3, 1, "HAVE SOMEONE");

                    }
                    break;
            }
            OLED_ShowString(4, 1, "             ");
            
            
            break;
    }
}
