/**
 ****************************************************************************************************
 * @file        dht11.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-26
 * @brief       DHT11数字温湿度传感器 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 MiniSTM32 V4开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20200426
 * 第一次发布
 *
 ****************************************************************************************************
 */

#include "dht11.h"
#include "delay.h"

uint8_t t = 0;
uint8_t temperature;
uint8_t humidity;

/**
 * @brief       复位DHT11
 * @param       data: 要写入的数据
 * @retval      无
 */
static void dht11_reset(void)
{
    DHT11_DQ_OUT(0);    /* 拉低DQ */
    delay_ms(20);       /* 拉低至少18ms */
    DHT11_DQ_OUT(1);    /* DQ=1 */
    delay_us(30);       /* 主机拉高10~35us */
}

/**
 * @brief       等待DHT11的回应
 * @param       无
 * @retval      0, DHT11正常
 *              1, DHT11异常/不存在
 */
uint8_t dht11_check(void)
{
    uint8_t retry = 0;
    uint8_t rval = 0;

    while (DHT11_DQ_IN && retry < 100)  /* DHT11会拉低约83us */
    {
        retry++;
        delay_us(1);
    }

    if (retry >= 100)
    {
        rval = 1;
    }
    else
    {
        retry = 0;

        while (!DHT11_DQ_IN && retry < 100) /* DHT11拉低后会再次拉高约87us */
        {
            retry++;
            delay_us(1);
        }
        if (retry >= 100) rval = 1;
    }
    
    return rval;
}

/**
 * @brief       从DHT11读取一个位
 * @param       无
 * @retval      读取到的位值: 0 / 1
 */
uint8_t dht11_read_bit(void)
{
    uint8_t retry = 0;

    while (DHT11_DQ_IN && retry < 100)  /* 等待变为低电平 */
    {
        retry++;
        delay_us(1);
    }

    retry = 0;

    while (!DHT11_DQ_IN && retry < 100) /* 等待变高电平 */
    {
        retry++;
        delay_us(1);
    }

    delay_us(40);       /* 等待40us */

    if (DHT11_DQ_IN)    /* 根据引脚状态返回 bit */
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

/**
 * @brief       从DHT11读取一个字节
 * @param       无
 * @retval      读到的数据
 */
static uint8_t dht11_read_byte(void)
{
    uint8_t i, data = 0;

    for (i = 0; i < 8; i++)         /* 循环读取8位数据 */
    {
        data <<= 1;                 /* 高位数据先输出, 先左移一位 */
        data |= dht11_read_bit();   /* 读取1bit数据 */
    }

    return data;
}

/**
 * @brief       从DHT11读取一次数据
 * @param       temp: 温度值(范围:-20~60°)
 * @param       humi: 湿度值(范围:5%~95%)
 * @retval      0, 正常.
 *              1, 失败
 */
uint8_t dht11_read_data(uint8_t *temp, uint8_t *humi)
{
    uint8_t buf[5];
    uint8_t i;
    dht11_reset();

    if (dht11_check() == 0)
    {
        for (i = 0; i < 5; i++)     /* 读取40位数据 */
        {
            buf[i] = dht11_read_byte();
        }

        if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
        {
            *humi = buf[0];
            *temp = buf[2];
        }
    }
    else
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief       初始化DHT11的IO口 DQ 同时检测DHT11的存在
 * @param       无
 * @retval      0, 正常
 *              1, 不存在/不正常
 */
uint8_t dht11_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    DHT11_DQ_GPIO_CLK_ENABLE();     /* 开启DQ引脚时钟 */

    gpio_init_struct.Pin = DHT11_DQ_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_OD;            /* 开漏输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(DHT11_DQ_GPIO_PORT, &gpio_init_struct);   /* 初始化DHT11_DQ引脚 */
    /* DHT11_DQ引脚模式设置,开漏输出,上拉, 这样就不用再设置IO方向了, 开漏输出的时候(=1), 也可以读取外部信号的高低电平 */

    dht11_reset();
    return dht11_check();
}

void DHT11_proc(void)
{
    if (t % 10 == 0) /* 每100ms读取一次 */
        {
            dht11_read_data(&temperature, &humidity);             /* 读取温湿度值 */
        }

        delay_ms(10);
        t++;

}






















