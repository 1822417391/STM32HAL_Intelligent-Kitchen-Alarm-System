#include "bsp_led.h"
/* �������ѣ�LED_YEL- PB13 LED_GRN- PB14 LED_RED- PB15*/
/*  */

/* LED��ʾ�Ƶ�3��״̬ */
/* LED״̬����̬�Ƶ�YEL����������GRN��������RED�� */
uint8_t LED_TIP[3] = {0,0,0};  //��ʼ���ƵƳ���

void led_disp(uint8_t *LED_TIP)
    {
    // ���ڼ�¼��ǰ LED ״̬����ʱ����
    uint8_t temp = 0x00;
    // ʹ�þ�̬��������¼֮ǰ LED ״̬�ı����������ж��Ƿ���Ҫ������ʾ
    static uint8_t temp_before = 0xff;  // ��ʼ��Ϊ 0�������һ�ν��뺯������������

    // ֻ���� LED_TIP �����ǰ3��Ԫ�أ���Ӧ PB13-PB15
    for (int i = 0; i < 3; i++)
        {
        // ����ǰԪ�ص�ֵ�����������õ� temp �����Ķ�Ӧλ
        if (LED_TIP[i] != 0) 
            { // ��� LED_TIP[i] Ϊ�� (����)
            temp |= (1 << i); // ���� temp �Ķ�ӦλΪ 1
            } 
            else 
            { // ��� LED_TIP[i] Ϊ�� (��)
            temp &= ~(1 << i); // ���� temp �Ķ�ӦλΪ 0
            }
        }

    // ������ǰ״̬��֮ǰ״̬��ͬ��ʱ�򣬲Ÿ�����ʾ
    if (temp != temp_before) 
        {
            if (temp & (1 << 0))
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
            }

            if (temp & (1 << 1))
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
            }

            if (temp & (1 << 2))
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
            }
            else
            {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
            }

            temp_before = temp;    // ���¼�¼�ľ�״̬
        }
}
    
/* �������ƣ�led_proc() */
/* �������ã�LED ��ʾ������ */
/*           ÿ�ε���led_proc()ʱ��LED ���� LED_TIP �����е�ֵ�������������ǹر� */
void led_proc(void)
{
    // �������� LED ״̬Ϊ�ر�
    LED_TIP[0] = 1;  // �Ƶ�
    LED_TIP[1] = 1;  // �̵�
    LED_TIP[2] = 1;  // ���   
    
    // ���ݵ�ǰ״̬���� LED ״̬
    if (currentStatus == NO_PERSON) {
        LED_TIP[0] = 0;  // ����״̬���Ƶ���
    }
    else if (currentStatus == PERSON_PRESENT) {
        LED_TIP[1] = 0;  // ����״̬���̵���
    }
    if(BEEP_state == 1)
    {
        LED_TIP[2] = 0;  
    }
    else
    {
        LED_TIP[2] = 1;  // ����״̬�������
    }
    //��ʾ��ǰ Led_Pos λ�õ� LED ��״̬
    led_disp(LED_TIP);

    
}
