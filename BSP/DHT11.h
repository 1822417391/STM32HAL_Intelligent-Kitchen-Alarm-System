#ifndef _DHT11_H
#define _DHT11_H

#include "stm32f1xx_hal.h"
#include "bsp_system.h"
#include "tim.h"

#define DT_Pin GPIO_PIN_8
#define DT_GPIO_Port GPIOA

void Delay_us(uint16_t us);
void DHT11_Rst(void);
void DHT11_proc(void);

extern uint8_t temp;
extern uint8_t humi;

extern uint8_t temperature;
extern uint8_t humidity;

uint8_t DHT11_Init(void);
uint8_t DHT11_Check(void);
uint8_t DHT11_Read_Bit(void);
uint8_t DHT11_Read_Byte(void);
uint8_t DHT11_Read_Data(uint8_t *temp, uint8_t *humi);

#endif

