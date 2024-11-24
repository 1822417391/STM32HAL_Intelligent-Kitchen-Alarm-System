#include "bsp_led_ui.h"
/* �������ѣ�LED1- PA9 LED2- PA10 LED3- PA11 LED4- PA12*/
/*  */

/* LED����Ƶ�4��״̬ */
/* LED_UI[0] -> PA9��״̬��LED_UI[1] -> PA10��״̬��....�Դ�����*/
uint8_t LED_UI[4] = {1,0,0,0};  //��ʼ��ֻ�н���1��

void led_ui_disp(uint8_t *LED_UI)
{
    // ���ڼ�¼��ǰ LED ״̬����ʱ����
    uint8_t temp = 0x00;
    // ʹ�þ�̬��������¼֮ǰ LED ״̬�ı����������ж��Ƿ���Ҫ������ʾ
    static uint8_t temp_before = 0xff;  // ��ʼ��Ϊ 0�������һ�ν��뺯������������

    // ֻ���� LED_UI �����ǰ4��Ԫ�أ���Ӧ PA9-PA12
    for (int i = 0; i < 4; i++) 
    {
        // ����ǰԪ�ص�ֵ�����������õ� temp �����Ķ�Ӧλ
        if (LED_UI[i]) 
            { // ��� LED_UI[i] Ϊ�� (����)
            temp |= (1 << i); // ���� temp �Ķ�ӦλΪ 1
            } 
        else 
            { // ��� ucLed[i] Ϊ�� (��)
            temp &= ~(1 << i); // ���� temp �Ķ�ӦλΪ 0
            }
    }

    // ������ǰ״̬��֮ǰ״̬��ͬ��ʱ�򣬲Ÿ�����ʾ
    if (temp != temp_before) 
    {
        // ʹ�� BSRR �Ĵ�������Ч�����ú��������
        // �����������ص�����
        GPIOA->BSRR = (0x0F << (9 + 16));  // �� PA9-PA12 �õͣ�+16 ��Ϊ�˷��� BSRR �ĵ� 16 λ (BRR)

        // ��������Ҫ�õ͵�����
        GPIOA->BSRR = ((~temp & 0x0F) << 9);         // ���� temp ��ֵ���� PA9-PA12


        temp_before = temp;    // ���¼�¼�ľ�״̬
    }


}

/* �������ƣ�led_ui_proc() */
/* �������ã�LED ��ʾ������ */
/*           ÿ�ε���led_ui_proc()ʱ��LED ���� LED_UI �����е�ֵ�������������ǹر� */
void led_ui_proc(void)
{

    //����OLED��ʾ�߼�д�ж��߼�
    LED_UI[0] = (oled_disp_mode == 0);
    LED_UI[1] = (oled_disp_mode == 1);
    LED_UI[2] = (oled_disp_mode == 2);
    LED_UI[3] = (oled_disp_mode == 3);
    
    //��ʾ��ǰ Led_Pos λ�õ� LED ��״̬
    led_ui_disp(LED_UI);
}
