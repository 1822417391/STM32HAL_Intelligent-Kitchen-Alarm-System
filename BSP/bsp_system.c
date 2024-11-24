#include "bsp_system.h"


void system_Init(void)
{
    // Configure PA9, PA10, PA11, PA12 as outputs
    GPIOA->CRH &= ~(0xFFFF << 4);  // Clear the configuration bits for PA9-PA12
    GPIOA->CRH |= (0x3333 << 4);   // Set PA9-PA12 as output push-pull 50MHz

    // Configure PB13, PB14, PB15 as outputs
    GPIOB->CRH &= ~((uint32_t)0xFFFF << 20); // Clear the configuration bits for PB13-PB15
    GPIOB->CRH |= ((uint32_t)0x3333 << 20);  // Set PB13-PB15 as output push-pull 50MHz

    // Set PA9, PA10, PA11, PA12 high
    GPIOA->BSRR |= (0x0F << 9);   // Set PA9-PA12 high using bit-set register

    // Set PB13, PB14, PB15 high
    GPIOB->BSRR |= (0x07 << 13);   // Set PB13-PB15 high using bit-set register
}
