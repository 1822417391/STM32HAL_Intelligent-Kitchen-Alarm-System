#include "bsp_adc.h"


// ���ڴ洢ADC��ȡ��MQ2������ֵ
uint16_t adc_value = 0;

void adc_proc(void)
{
    // ����ADC����ȡֵ
    HAL_ADC_Start(&hadc1); 
    if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK) 
    {
        // ��ȡADC��ֵ
        adc_value = HAL_ADC_GetValue(&hadc1);
    }
    HAL_ADC_Stop(&hadc1);

}

