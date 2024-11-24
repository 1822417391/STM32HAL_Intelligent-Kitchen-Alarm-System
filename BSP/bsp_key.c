#include "bsp_key.h"

/* �Զ�������� */
uint8_t key_val = 0; //��ǰ����״̬
uint8_t key_before = 0;  //ǰһ�ΰ���״̬
uint8_t key_down = 0;    //���µİ���
uint8_t key_up = 0;  //�ص��İ���

/* �������ƣ�key_read() */
/* �������ã��ú�����ȡ������ GPIO �����ϵİ���״̬����������Ӧ�İ������ */
/* ��������ֵ��return��: 0 ��ʾû�а��� 1-4 ��ʾ��Ӧ�İ��������� */
uint8_t key_read(void)
{
    //���ڴ洢����״̬����ʱ����
    uint8_t temp = 0;
    
    //��� GPIOA ����4 ��״̬
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7) == GPIO_PIN_RESET)
        temp =1;    //�������״̬Ϊ RESET���򰴼� 1 ������
    
    //��� GPIOA ����5 ��״̬
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6) == GPIO_PIN_RESET)
        temp =2;    //�������״̬Ϊ RESET���򰴼� 2 ������
    
    //��� GPIOA ����6 ��״̬
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5) == GPIO_PIN_RESET)
        temp =3;    //�������״̬Ϊ RESET���򰴼� 3 ������
    
    //��� GPIOA ����7 ��״̬
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) == GPIO_PIN_RESET)
        temp =4;    //�������״̬Ϊ RESET���򰴼� 4 ������
    
    //��� GPIOB ����8 ��״̬
    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8) == GPIO_PIN_RESET)
        temp =5;    //�������״̬Ϊ RESET���򰴼� 5 ������   
    
    //���ؼ�⵽�İ������
    return temp;
}


/* �������ƣ�key_proc() */
/* �������ã��ú�������ɨ�谴����״̬�������°������º��ͷŵı�־ */
/* key_val����ǰ״̬ key_before���ϴ�״̬ key_down���������� key_up������̧�� */
void key_proc(void)
{
    //��ȡ��ǰ����״̬
    key_val = key_read();
    //���㰴�µİ�������ǰ����״̬��ǰһ״̬��򣬲��뵱ǰ״̬���룩
    key_down = key_val & (key_before ^ key_val);
    //�������̧��İ�������ǰδ����״̬��ǰһ״̬��򣬲���ǰһ״̬���룩
    key_up = ~key_val & (key_before ^ key_val);
    //����ǰһ����״̬
    key_before = key_val;
    
    switch(key_down)
    {
        case 1:
            oled_disp_mode = 0;
            //LED_UI[0] = 1;
            break;
        
        case 2:
            oled_disp_mode = 1;
            //LED_UI[1] = 1;
            break;
        
        case 3:
            oled_disp_mode = 2;
            //LED_UI[2] = 1;
            break;
        
        case 4:
            oled_disp_mode = 3;
            //LED_UI[3] = 1;
            break;

//        default:
//            // Reset all LEDs if no valid key is pressed
//            LED_UI[0] = 0;
//            LED_UI[1] = 0;
//            LED_UI[2] = 0;
//            LED_UI[3] = 0;
//            break;
    }

    // ���ú�������LED״̬��Ӳ��
    //led_ui_disp(LED_UI);
}
