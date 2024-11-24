# STM32HAL_Intelligent-Kitchen-Alarm-System
## 用STM32HAL库基于传感器的智能厨房报警系统课设设计介绍

## 1软件部分开源介绍

### 1.1软件部分使用软件：

STM32CubeMX、Keil5。本课设通过HAL库进行开发，使用<u>类RTOS的操作系统</u>来控制多个传感器之间的运行与阻塞时间调度。主要思想通过<u>模块化</u>封装各个传感器的逻辑判断、底层驱动通过<u>调度器</u>(bsp_shceduler.c)进行驱动，故有很多自己创立的库，还请各位见谅。

### 1.2主要文件夹作用声明 ：

![部分接口图解](https://github.com/user-attachments/assets/4075f0d5-e9c7-4373-9d9f-31d36954c1aa)


**·BSP：**绝大部分的自定义.c.h文件存放在这，用于底层设置和驱动。
**·DHT11：**由于DHT11对时序要求非常严格，曾经写了很多次都没办法成功读到DHT11的数据，后面通过CSDN其中一篇文章对DHT11延时影响的分析让我有了灵感，通过引入正点原子的delay库，统一延时影响，消除使用定时器配置与HAL_Delay()导致的误差影响，并且为了保正DHT11初始化与后续正常工作，将其独立列在main.c的while()中，与调度器同级运行。

**·HCSR501/OLED ：**都是他们各自的驱动库，OLED采用IIC通信还有自定义的字库，HCSR501同理，具体见代码。



## 2.硬件部分开源介绍

### 2.1硬件部分使用软件：

嘉立创EDA，简单好用（主要是打板免费）。

### 2.2具体开源连接传送门：立创硬件开源平台



### 3.关于迭代

对于后续该系统暂时不考虑更新维护，原因其为本人的一个课程作业，大部分功能都完成了，对于PCB的Layout存在很多不合理的部分，这也是我第一次开源，希望能够解各位完成期末课设人的一个选题燃眉之急，谢谢！
