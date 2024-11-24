#include "bsp_adc.h"


// 用于存储ADC读取的MQ2传感器值
uint16_t adc_value = 0;

void adc_proc(void)
{
    // 启动ADC并读取值
    HAL_ADC_Start(&hadc1); 
    if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK) 
    {
        // 获取ADC的值
        adc_value = HAL_ADC_GetValue(&hadc1);
    }
    HAL_ADC_Stop(&hadc1);

}

