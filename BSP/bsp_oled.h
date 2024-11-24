#ifndef  _BSP_OLED_H_
#define  _BSP_OLED_H_
#define MQ2_THRESHOLD 2000

#include "bsp_system.h"

void oled_proc(void);
void OLEDSprintf(uint8_t Line, uint8_t Column, const char *format, ...);

typedef enum {
    NO_PERSON = 0,
    PERSON_PRESENT,
} HumanStatus;

extern HumanStatus currentStatus;

#endif
