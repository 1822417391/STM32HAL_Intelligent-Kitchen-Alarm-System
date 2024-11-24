#ifndef __BSP_BEEP_H__
#define __BSP_BEEP_H__

#include "bsp_system.h"

void beep_proc(void);
void warning_proc(void);
extern volatile uint16_t BEEP_state;
#endif

