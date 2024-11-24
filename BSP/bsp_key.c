#include "bsp_key.h"

/* 自定义变量区 */
uint8_t key_val = 0; //当前按键状态
uint8_t key_before = 0;  //前一次按键状态
uint8_t key_down = 0;    //按下的按键
uint8_t key_up = 0;  //回弹的按键

/* 函数名称：key_read() */
/* 函数作用：该函数读取连接在 GPIO 引脚上的按键状态，并返回相应的按键编号 */
/* 函数返回值（return）: 0 表示没有按下 1-4 表示对应的按键被按下 */
uint8_t key_read(void)
{
    //用于存储按键状态的临时变量
    uint8_t temp = 0;
    
    //检查 GPIOA 引脚4 的状态
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7) == GPIO_PIN_RESET)
        temp =1;    //如果引脚状态为 RESET，则按键 1 被按下
    
    //检查 GPIOA 引脚5 的状态
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6) == GPIO_PIN_RESET)
        temp =2;    //如果引脚状态为 RESET，则按键 2 被按下
    
    //检查 GPIOA 引脚6 的状态
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5) == GPIO_PIN_RESET)
        temp =3;    //如果引脚状态为 RESET，则按键 3 被按下
    
    //检查 GPIOA 引脚7 的状态
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) == GPIO_PIN_RESET)
        temp =4;    //如果引脚状态为 RESET，则按键 4 被按下
    
    //检查 GPIOB 引脚8 的状态
    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8) == GPIO_PIN_RESET)
        temp =5;    //如果引脚状态为 RESET，则按键 5 被按下   
    
    //返回检测到的按键编号
    return temp;
}


/* 函数名称：key_proc() */
/* 函数作用：该函数用于扫描按键的状态，并更新按键按下和释放的标志 */
/* key_val：当前状态 key_before：上次状态 key_down：按键按下 key_up：按键抬起 */
void key_proc(void)
{
    //读取当前按键状态
    key_val = key_read();
    //计算按下的按键（当前按下状态与前一状态异或，并与当前状态相与）
    key_down = key_val & (key_before ^ key_val);
    //计算放下抬起的按键（当前未按下状态与前一状态异或，并于前一状态相与）
    key_up = ~key_val & (key_before ^ key_val);
    //更新前一按键状态
    key_before = key_val;
    
    switch(key_down)
    {
        case 1:
            oled_disp_mode = 0;
            //LED_UI[0] = 1;
            break;
        
        case 2:
            oled_disp_mode = 1;
            //LED_UI[1] = 1;
            break;
        
        case 3:
            oled_disp_mode = 2;
            //LED_UI[2] = 1;
            break;
        
        case 4:
            oled_disp_mode = 3;
            //LED_UI[3] = 1;
            break;

//        default:
//            // Reset all LEDs if no valid key is pressed
//            LED_UI[0] = 0;
//            LED_UI[1] = 0;
//            LED_UI[2] = 0;
//            LED_UI[3] = 0;
//            break;
    }

    // 调用函数更新LED状态到硬件
    //led_ui_disp(LED_UI);
}
