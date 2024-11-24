#include "DHT11.h"

uint8_t temperature = 0;
uint8_t humidity = 0;

extern TIM_HandleTypeDef htim2;  // TIM2句柄引用

// 使用TIM2实现微秒级延时
void Delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim2, 0);  // 重置计数器
    HAL_TIM_Base_Start(&htim2);        // 启动定时器

    while (__HAL_TIM_GET_COUNTER(&htim2) < us)
        ;  // 等待计数器达到所需微秒数

    HAL_TIM_Base_Stop(&htim2);         // 停止定时器
}

// 初始化DHT11的IO口 DQ 同时检测DHT11的存在
// 返回1: 不存在
// 返回0: 存在
uint8_t DHT11_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能GPIOA时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置GPIO引脚：推挽输出，高速
    GPIO_InitStruct.Pin = DT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DT_GPIO_Port, &GPIO_InitStruct);

    // 设置初始状态为高电平
    HAL_GPIO_WritePin(DT_GPIO_Port, DT_Pin, GPIO_PIN_SET);

    // 复位DHT11
    DHT11_Rst();

    // 检测DHT11的回应
    return DHT11_Check();
}

// 复位DHT11
void DHT11_Rst(void)
{
    // 配置为输出模式
    HAL_GPIO_WritePin(DT_GPIO_Port, DT_Pin, GPIO_PIN_RESET); // 拉低DQ
    HAL_Delay(20);                                           // 延迟至少18ms
    HAL_GPIO_WritePin(DT_GPIO_Port, DT_Pin, GPIO_PIN_SET);   // DQ拉高
    Delay_us(30);                                            // 延迟20~40us
}

// 检测DHT11是否存在
uint8_t DHT11_Check(void)
{
    uint8_t retry = 0;

    // 配置为输入模式
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DT_GPIO_Port, &GPIO_InitStruct);

    // 等待DHT11的低电平信号
    while (HAL_GPIO_ReadPin(DT_GPIO_Port, DT_Pin) && retry < 100)
    {
        retry++;
        Delay_us(1); // 使用自定义微秒延迟函数
    }
    if (retry >= 100) return 1;
    retry = 0;

    // 等待DHT11的高电平信号
    while (!HAL_GPIO_ReadPin(DT_GPIO_Port, DT_Pin) && retry < 100)
    {
        retry++;
        Delay_us(1);
    }
    if (retry >= 100) return 1;

    return 0;
}

// 读取DHT11的一位
uint8_t DHT11_Read_Bit(void)
{
    uint8_t retry = 0;

    while (HAL_GPIO_ReadPin(DT_GPIO_Port, DT_Pin) && retry < 100)
    {
        retry++;
        Delay_us(1);
    }
    retry = 0;

    while (!HAL_GPIO_ReadPin(DT_GPIO_Port, DT_Pin) && retry < 100)
    {
        retry++;
        Delay_us(1);
    }

    Delay_us(40); // 延迟40us
    return HAL_GPIO_ReadPin(DT_GPIO_Port, DT_Pin) ? 1 : 0;
}

// 读取DHT11的一个字节
uint8_t DHT11_Read_Byte(void)
{
    uint8_t i, dat = 0;
    for (i = 0; i < 8; i++)
    {
        dat <<= 1;
        dat |= DHT11_Read_Bit();
    }
    return dat;
}

// 从DHT11读取一次数据
uint8_t DHT11_Read_Data(uint8_t *temp, uint8_t *humi)
{
    uint8_t buf[5] = {0};
    uint8_t i;

    DHT11_Rst();
    if (DHT11_Check() == 0)
    {
        for (i = 0; i < 5; i++)
        {
            buf[i] = DHT11_Read_Byte();
        }
        if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
        {
            *humi = buf[0];
            *temp = buf[2];
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

void DHT11_proc(void)
{
    static uint32_t last_update_time = 0;
    uint32_t current_time = HAL_GetTick(); // 获取当前系统时间

    if (current_time - last_update_time >= 2000) 
        
        {
            last_update_time = current_time;
            uint8_t temp = 0;
            uint8_t humi = 0;

        // 尝试读取数据并检查是否成功
        if (DHT11_Read_Data(&temp, &humi) == 0)  // 返回0表示成功
            
            {
                temperature = temp;
                humidity = humi;
            }
        else
            {
            // 如果读取失败，可以输出错误或做其他处理
            OLEDSprintf(4,1,"DHT11 ERROR");
            }
            
        }

}
