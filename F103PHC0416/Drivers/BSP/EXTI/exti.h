/**
 ****************************************************************************************************
 * @file        exti.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-20
 * @brief       外部中断 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20200419
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __EXTI_H
#define __EXTI_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* 引脚 和 中断编号 & 中断服务函数 定义 */ 

#define MPU6050_INT_GPIO_PORT              GPIOB
#define MPU6050_INT_GPIO_PIN               GPIO_PIN_12
#define MPU6050_INT_GPIO_CLK_ENABLE()      do{  __HAL_RCC_GPIOB_CLK_ENABLE();  \
                                                __HAL_RCC_AFIO_CLK_ENABLE();    \
                                              }while(0)   /* PA口时钟使能 */
                                             
#define MPU6050_INT_IRQn                   EXTI15_10_IRQn
#define MPU6050_INT_IRQHandler             EXTI15_10_IRQHandler



/******************************************************************************************/


void MPU6050_extix_init(void);  /* 外部中断初始化 */

#endif

























