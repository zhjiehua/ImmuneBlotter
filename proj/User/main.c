/*
*********************************************************************************************************
*	                                  
*	模块名称 : 主程序模块。
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : STemWin配套例程
*              实验内容：
*                 1. 学习emWin教程第3章配套的例子
*              注意事项：
*                 1. 本实验推荐使用串口软件SecureCRT，要不串口打印效果不整齐。此软件在
*                    V4开发板光盘里面有。
*                 2. 务必将编辑器的缩进参数和TAB设置为4来阅读本文件，要不代码显示不整齐。
*                 3. 使用3.5寸ili9488屏的触摸功能时，不要再使用LED1，因为LED1使用的引脚
*                    和SPI Flash的片选引脚公用。操作触摸的时候进行LED1闪烁会导致也操作SPI Flash。
*                    从而造成触摸混乱。
*
*	修改记录 :
*		版本号    日期         作者            说明
*       V1.0    2015-09-28   Eric2013    1. ST固件库到V3.6.1版本
*                                        2. BSP驱动包V1.2
*                                        3. STemWin版本V5.28   
*
*      Copyright (C), 2015-2020, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"			/* 底层硬件驱动 */
#include "MainTask.h"


/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参: 无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/
int main(void)
{
	bsp_Init();	/* 为了是main函数看起来更简洁些，我们将硬件初始化的代码封装到这个函数 */
	
	MainTask();
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
