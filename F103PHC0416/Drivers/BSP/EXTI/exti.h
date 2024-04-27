/**
 ****************************************************************************************************
 * @file        exti.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-20
 * @brief       �ⲿ�ж� ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20200419
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __EXTI_H
#define __EXTI_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* ���� �� �жϱ�� & �жϷ����� ���� */ 

#define MPU6050_INT_GPIO_PORT              GPIOB
#define MPU6050_INT_GPIO_PIN               GPIO_PIN_12
#define MPU6050_INT_GPIO_CLK_ENABLE()      do{  __HAL_RCC_GPIOB_CLK_ENABLE();  \
                                                __HAL_RCC_AFIO_CLK_ENABLE();    \
                                              }while(0)   /* PA��ʱ��ʹ�� */
                                             
#define MPU6050_INT_IRQn                   EXTI15_10_IRQn
#define MPU6050_INT_IRQHandler             EXTI15_10_IRQHandler



/******************************************************************************************/


void MPU6050_extix_init(void);  /* �ⲿ�жϳ�ʼ�� */

#endif

























