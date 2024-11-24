#ifndef __BODY_HW_H
#define	__BODY_HW_H
#include "stm32f1xx_hal.h"
#include "bsp_system.h"

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	HC-SR501人体红外传感器h文件                   
 * 版本			: V1.0
 * 日期			: 2024.8.26
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/


/***************根据自己需求更改****************/
// BODY_HW GPIO宏定义

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

