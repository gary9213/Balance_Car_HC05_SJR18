/**
 ****************************************************************************************************
 * @file        exti.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-19
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
 * V1.0 20200420
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/ATK_MD0096/atk_md0096.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/ATK_MS6050/atk_ms6050.h"
#include "./BSP/ATK_MS6050/eMPL/inv_mpu.h"
#include "./BSP/PID/pid.h"
/**
 * @brief       KEY0 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void MPU6050_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(MPU6050_INT_GPIO_PIN);         /* �����жϴ����ú��� ����ж��� ���жϱ�־λ */
    __HAL_GPIO_EXTI_CLEAR_IT(MPU6050_INT_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}



uint8_t ret_exit=0;


float pit, rol, yaw;
int16_t acc_x, acc_y, acc_z;
int16_t gyr_x, gyr_y, gyr_z;
int16_t temp;
float temp_pit;
uint8_t Control_START_Flag=0;


/**
 * @brief       �жϷ����������Ҫ��������
                ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @param       GPIO_Pin:�ж����ź�
 * @retval      ��
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//    printf("�����ж�");
    switch(GPIO_Pin)
    {
        case MPU6050_INT_GPIO_PIN:
//            printf(" MPU6050�����ж�");
        /* ��ȡATK-MS6050 DMP���������� */
        ret_exit += atk_ms6050_dmp_get_data(&pit, &rol, &yaw);

        /* ��ȡATK-MS6050���ٶ�ֵ */
        ret_exit += atk_ms6050_get_accelerometer(&acc_x, &acc_y, &acc_z);

        /* ��ȡATK-MS6050������ֵ */
        ret_exit += atk_ms6050_get_gyroscope(&gyr_x, &gyr_y, &gyr_z);

        /* ��ȡATK-MS6050�¶�ֵ */
        ret_exit += atk_ms6050_get_temperature(&temp);

        if (ret_exit == 0)
        {
                //printf("pit :  %f  \r\n",rol);
                //printf("rol:       %f",rol);
               // printf("yaw:%f",yaw);
              // printf("gyr_y:      %d\r\n",gyr_y);
 
             PID_control();

                
                temp_pit=rol;

            
            
            /* ��LCD����ʾ���������Ϣ */
               
        }
        ret_exit = 0;
        break;
        
        default:break;
                
        
    }
}

/**
 * @brief       �ⲿ�жϳ�ʼ������
 * @param       ��
 * @retval      ��
 */
void MPU6050_extix_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    MPU6050_INT_GPIO_CLK_ENABLE();                              /* KEY0ʱ��ʹ�� */


    gpio_init_struct.Pin = MPU6050_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* �½��ش��� */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(MPU6050_INT_GPIO_PORT, &gpio_init_struct);    /* KEY0����Ϊ�½��ش����ж� */
    
    HAL_NVIC_SetPriority(MPU6050_INT_IRQn, 2, 2);               /* ��ռ2�������ȼ�2 */
    HAL_NVIC_EnableIRQ(MPU6050_INT_IRQn);                       /* ʹ���ж���15 */

}












