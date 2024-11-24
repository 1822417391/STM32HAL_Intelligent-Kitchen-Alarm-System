#include "bsp_beep.h"

volatile uint16_t BEEP_state = 1;    //��������־λ��1���У�0��

void warning_proc(void)
{
    // ��ȡPB9���ŵ�ƽ
    GPIO_PinState pb9_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
    uint16_t smoke_level = adc_value;
    
    //�����ж�
    if(temperature > 60)
    {
        BEEP_state = 0;
        return;
    }
    
    //�����ж�
    if(smoke_level > MQ2_THRESHOLD)
    {
        BEEP_state = 0;
        return;
    }
    
    //��ˮ�ж�
    if (pb9_state == GPIO_PIN_SET)
    {
        BEEP_state = 0;
        return;
    }
    
    //�����û�����͹رշ�����
    BEEP_state = 1;
}

void beep_proc(void)
{
    if (BEEP_state == 0)
    {
        // BEEP_state == 0 ʱ������͵�ƽ����������
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);  // ���� PB4 Ϊ�͵�ƽ

    }
    else
    {
        // BEEP_state == 1 ʱ������ߵ�ƽ�رշ�����
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);    // ���� PB4 Ϊ�ߵ�ƽ

    }
}
