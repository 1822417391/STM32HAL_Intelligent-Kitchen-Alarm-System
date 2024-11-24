#include "bsp_oled.h"


HumanStatus currentStatus = NO_PERSON;

/* �ļ����ƣ�bsp_oled.c */
/* �ļ����ã���ʽ���ַ�������ʾ��ָ���� OLED ����  */

/* 
 *
 * ����˵����
 * Line      Ҫ��ʾ�ַ����� OLED �к�
 * format    ��ʽ���ַ��������Ҫ��ʽ�����ַ���
 *
 * ����������
 * vsprintf  ��ʽ���ַ���������'OLED_DisplayStringLine' ��ʾ��ʽ������ַ���
 *
 * ʾ���÷���
 * OLEDSprintf(1, 1, "Hello, world!");  // �ڵ�һ�е�һ����ʾ "Hello, world!"
 * OLEDSprintf(2, 1, "Counter: %d", counter); // �ڵڶ��е�һ����ʾ������ֵ
 * OLEDSprintf(3, 1, "Float: %.2f", 3.14159);  // �ڵ����е�һ����ʾ��������������λС��
 *
 */
void OLEDSprintf(uint8_t Line, uint8_t Column, const char *format, ...)
{
    char String[17]; // ���ӻ�������С�������ɸ������ַ�����OLED������Ϊ16
    va_list arg;
    va_start(arg, format);
    vsnprintf(String, sizeof(String), format, arg); // ʹ�� vsnprintf ���⻺�������
    va_end(arg);    //��������б�
    OLED_ShowString(Line, Column, String);  // ��ʾ�ַ�����OLED
}

uint8_t oled_disp_mode = 0 ;// ��ʾOLEDģʽ, = 0��ʪ�ȼ�����/ = 1��ˮ������/ = 2���������/ = 3������ڼ�����

void oled_proc(void)
{
    // ��ȡPB9���ŵ�ƽ
    GPIO_PinState pb9_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
    
    switch(oled_disp_mode)
    {
        // DHT11�¶ȼ�����
        case 0:            
            OLEDSprintf(1, 6, "DHT11");
            OLEDSprintf(2, 1, "Temp: %dC        ", temperature);
            OLEDSprintf(3, 1, "Humi: %d%%Rh     ", humidity);
            if(temperature > 60)
            {
                OLED_ShowString(4, 1, "WARNING!    ");
            }
            else{
                OLED_ShowString(4, 1, "SAFE         ");
            }
            break;

        // ��ˮ������
        case 1:
            OLED_ShowString(1, 6, "WATER");
        
             if (pb9_state == GPIO_PIN_RESET) // �͵�ƽ
            { 
                // ��ˮ��ʾ
                OLED_ShowString(2,1,"WATER <HIGH>   ");
                OLED_ShowString(3, 1, "WARNING!    ");
                
            }
            else if (pb9_state == GPIO_PIN_SET) // �ߵ�ƽ
            { 
                // û��ˮ��ʾ
                OLED_ShowString(2,1,"WATER <LOW>    ");
                OLED_ShowString(3, 1, "SAFE         ");
            } 
            OLED_ShowString(4, 1, "             ");
            break;

        // ���������
        case 2:
            OLED_ShowString(1, 6, "SMOKE");
                // ��ӡ��Ϣ���ж���ֵ
            OLEDSprintf(2,1,"Value: %d     ", adc_value);
            if(adc_value <= MQ2_THRESHOLD)
            {
                OLED_ShowString(3, 1, "SAFE         ");
            }
            else
            {
                OLED_ShowString(3, 1, "WARNING!    ");
            }
            OLED_ShowString(4, 1, "             ");
            break;

        // ������ڼ�����
        case 3:
            OLED_ShowString(1, 6, "HUMAN");
            OLED_ShowString(2, 1, "HAVE ANYONE?");

            switch (currentStatus)
            {
                case NO_PERSON:
                    if (value == GPIO_PIN_SET) 
                    {
                        // ��⵽���˵��źţ��л������˵�״̬
                        currentStatus = PERSON_PRESENT;
                        OLED_ShowString(3, 1, "HAVE SOMEONE");

                    } 
                    else 
                    {
                        OLED_ShowString(3, 1, "NOBODY          ");

                    }
                    break;

                case PERSON_PRESENT:
                    if (value == GPIO_PIN_RESET) 
                    {
                        // ��⵽û���˵��źţ��л���û���˵�״̬
                        currentStatus = NO_PERSON;
                        OLED_ShowString(3, 1, "NOBODY          ");

                    } 
                    else 
                    {
                        OLED_ShowString(3, 1, "HAVE SOMEONE");

                    }
                    break;
            }
            OLED_ShowString(4, 1, "             ");
            
            
            break;
    }
}
