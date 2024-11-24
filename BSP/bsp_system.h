#ifndef __BSP_SYSTEM_H__
#define __BSP_SYSTEM_H__

//��ͷ�ļ���
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

//��ͷ�ļ���
#include "main.h"
#include "bsp_led_ui.h"
#include "bsp_scheduler.h"
#include "ringbuffer.h"
#include "bsp_key.h"
#include "bsp_led.h"

#include "bsp_oled.h"
#include "OLED.h"
#include "sys.h"
#include "delay.h"
#include "dht11.h"
#include "body_hw.h"
#include "math.h"
#include "bsp_adc.h"
#include "bsp_beep.h"
#include "bsp_water.h"

//�ؼ��ֱ���������
extern uint8_t LED_UI[4];
extern uint8_t LED_TIP[3];
extern uint8_t oled_disp_mode;

extern uint32_t dma_buff[1][30];//DMA���ջ���

#endif
