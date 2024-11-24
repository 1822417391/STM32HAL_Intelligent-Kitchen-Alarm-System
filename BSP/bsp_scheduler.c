#include "bsp_scheduler.h"

/* 文件名称：bsp_scheduler.c */
/* 文件作用：任务调度，类操作系统FREERTOS */

/* 自定义变量区 */
uint8_t task_num;   //全局变量，用于存储任务数量

/* ************************************* */
typedef struct{//定义一个任务结构体，其中包括：任务名/执行周期/上次周期间隔
     void(*task_func)(void);//设定:任务名
     uint32_t rate_ms;  //设定:任务执行周期ms
     uint32_t last_run;  //设定:距离上一次运行周期间隔ms
}    task_t;   


/* 静态任务数组，每个任务包含任务函数、执行周期ms和上次运行时间ms */
static task_t scheduler_task[] =
{
    {key_proc,10,0}, //定义一个任务，任务函数为 Key_Proc,执行周期为10ms，初始上次运行时间为0ms。
    {led_ui_proc,10,0}, //定义一个任务，任务函数为 Led_UI_Proc,执行周期为10ms，初始上次运行时间为0ms。
    {adc_proc,500,0}, //定义一个任务，任务函数为 adc_Proc,执行周期为100ms，初始上次运行时间为0ms。
    {beep_proc,100,0}, //定义一个任务，任务函数为 Beep_Proc,执行周期为100ms，初始上次运行时间为0ms。
    {water_proc,200,0}, //定义一个任务，任务函数为 Water_Proc,执行周期为200ms，初始上次运行时间为0ms。
    {oled_proc,100,0}, //定义一个任务，任务函数为 OLED_Proc,执行周期为100ms，初始上次运行时间为0ms。
    {warning_proc,100,0}, //定义一个任务，任务函数为 Warning_Proc,执行周期为100ms，初始上次运行时间为0ms。
    {led_proc,100,0}, //定义一个任务，任务函数为 Led_Proc,执行周期为100ms，初始上次运行时间为0ms。
};

/* 函数名称：scheduler_init() */
/* 函数作用：调度机初始化函数 */
/*           计算任务数组的元素个数，并将结果存储在 task_num 中 */
void scheduler_init(void)
{
     task_num = sizeof(scheduler_task) / sizeof(task_t);//计算任务数组的元素个数，并将结果存储在 task_num 中
}

/* 函数名称：scheduler_run() */
/* 函数作用：调度机运行函数 */
/* 遍历任务数组，检查是否有任务需要执行。如果当前时间已经超过任务的执行周期，则执行任务并更新上次时间 */
void scheduler_run(void)
{   
    //测试
    //OLEDSprintf(4,1,"updataOK");
    //遍历任务数组中的所有任务
    for(uint8_t i =0;i < task_num;i++)
    {
        //自建变量now_time获取当前的系统时间（毫秒）
        uint32_t now_time = HAL_GetTick();
        
        //检查当前时间是否达到任务的执行时间
        if(now_time >= scheduler_task[i].rate_ms + scheduler_task[i].last_run)
        {
            //更新任务的上次运行时间为当前的时间
            scheduler_task[i].last_run = now_time;
            
            //执行任务函数
            scheduler_task[i].task_func();
        }
    }
}

