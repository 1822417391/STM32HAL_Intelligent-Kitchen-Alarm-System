#include "bsp_scheduler.h"

/* �ļ����ƣ�bsp_scheduler.c */
/* �ļ����ã�������ȣ������ϵͳFREERTOS */

/* �Զ�������� */
uint8_t task_num;   //ȫ�ֱ��������ڴ洢��������

/* ************************************* */
typedef struct{//����һ������ṹ�壬���а�����������/ִ������/�ϴ����ڼ��
     void(*task_func)(void);//�趨:������
     uint32_t rate_ms;  //�趨:����ִ������ms
     uint32_t last_run;  //�趨:������һ���������ڼ��ms
}    task_t;   


/* ��̬�������飬ÿ�����������������ִ������ms���ϴ�����ʱ��ms */
static task_t scheduler_task[] =
{
    {key_proc,10,0}, //����һ������������Ϊ Key_Proc,ִ������Ϊ10ms����ʼ�ϴ�����ʱ��Ϊ0ms��
    {led_ui_proc,10,0}, //����һ������������Ϊ Led_UI_Proc,ִ������Ϊ10ms����ʼ�ϴ�����ʱ��Ϊ0ms��
    {adc_proc,500,0}, //����һ������������Ϊ adc_Proc,ִ������Ϊ100ms����ʼ�ϴ�����ʱ��Ϊ0ms��
    {beep_proc,100,0}, //����һ������������Ϊ Beep_Proc,ִ������Ϊ100ms����ʼ�ϴ�����ʱ��Ϊ0ms��
    {water_proc,200,0}, //����һ������������Ϊ Water_Proc,ִ������Ϊ200ms����ʼ�ϴ�����ʱ��Ϊ0ms��
    {oled_proc,100,0}, //����һ������������Ϊ OLED_Proc,ִ������Ϊ100ms����ʼ�ϴ�����ʱ��Ϊ0ms��
    {warning_proc,100,0}, //����һ������������Ϊ Warning_Proc,ִ������Ϊ100ms����ʼ�ϴ�����ʱ��Ϊ0ms��
    {led_proc,100,0}, //����һ������������Ϊ Led_Proc,ִ������Ϊ100ms����ʼ�ϴ�����ʱ��Ϊ0ms��
};

/* �������ƣ�scheduler_init() */
/* �������ã����Ȼ���ʼ������ */
/*           �������������Ԫ�ظ�������������洢�� task_num �� */
void scheduler_init(void)
{
     task_num = sizeof(scheduler_task) / sizeof(task_t);//�������������Ԫ�ظ�������������洢�� task_num ��
}

/* �������ƣ�scheduler_run() */
/* �������ã����Ȼ����к��� */
/* �����������飬����Ƿ���������Ҫִ�С������ǰʱ���Ѿ����������ִ�����ڣ���ִ�����񲢸����ϴ�ʱ�� */
void scheduler_run(void)
{   
    //����
    //OLEDSprintf(4,1,"updataOK");
    //�������������е���������
    for(uint8_t i =0;i < task_num;i++)
    {
        //�Խ�����now_time��ȡ��ǰ��ϵͳʱ�䣨���룩
        uint32_t now_time = HAL_GetTick();
        
        //��鵱ǰʱ���Ƿ�ﵽ�����ִ��ʱ��
        if(now_time >= scheduler_task[i].rate_ms + scheduler_task[i].last_run)
        {
            //����������ϴ�����ʱ��Ϊ��ǰ��ʱ��
            scheduler_task[i].last_run = now_time;
            
            //ִ��������
            scheduler_task[i].task_func();
        }
    }
}

