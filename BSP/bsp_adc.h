#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "bsp_system.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
void adc_proc(void);

extern uint16_t adc_value;
#endif
