#ifndef __BODY_HW_H
#define	__BODY_HW_H
#include "stm32f1xx_hal.h"
#include "bsp_system.h"

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	HC-SR501������⴫����h�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.8.26
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/


/***************�����Լ��������****************/
// BODY_HW GPIO�궨��

#define		BODY_HW_GPIO_CLK								RCC_APB2Periph_GPIOB
#define 	BODY_HW_GPIO_PORT								GPIOB
#define 	BODY_HW_GPIO_PIN								GPIO_PIN_12			

/*********************END**********************/


void BODY_HW_Init(void);
uint16_t BODY_HW_GetData(void);
void HCSR501_proc(void);

extern uint16_t People_Data;
extern uint16_t value;

#endif /* __ADC_H */

