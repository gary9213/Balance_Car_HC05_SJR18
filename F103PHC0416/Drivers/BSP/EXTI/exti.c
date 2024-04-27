/**
 ****************************************************************************************************
 * @file        exti.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-19
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
 * V1.0 20200420
 * 第一次发布
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
 * @brief       KEY0 外部中断服务程序
 * @param       无
 * @retval      无
 */
void MPU6050_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(MPU6050_INT_GPIO_PIN);         /* 调用中断处理公用函数 清除中断线 的中断标志位 */
    __HAL_GPIO_EXTI_CLEAR_IT(MPU6050_INT_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}



uint8_t ret_exit=0;


float pit, rol, yaw;
int16_t acc_x, acc_y, acc_z;
int16_t gyr_x, gyr_y, gyr_z;
int16_t temp;
float temp_pit;
uint8_t Control_START_Flag=0;


/**
 * @brief       中断服务程序中需要做的事情
                在HAL库中所有的外部中断服务函数都会调用此函数
 * @param       GPIO_Pin:中断引脚号
 * @retval      无
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//    printf("触发中断");
    switch(GPIO_Pin)
    {
        case MPU6050_INT_GPIO_PIN:
//            printf(" MPU6050触发中断");
        /* 获取ATK-MS6050 DMP处理后的数据 */
        ret_exit += atk_ms6050_dmp_get_data(&pit, &rol, &yaw);

        /* 获取ATK-MS6050加速度值 */
        ret_exit += atk_ms6050_get_accelerometer(&acc_x, &acc_y, &acc_z);

        /* 获取ATK-MS6050陀螺仪值 */
        ret_exit += atk_ms6050_get_gyroscope(&gyr_x, &gyr_y, &gyr_z);

        /* 获取ATK-MS6050温度值 */
        ret_exit += atk_ms6050_get_temperature(&temp);

        if (ret_exit == 0)
        {
                //printf("pit :  %f  \r\n",rol);
                //printf("rol:       %f",rol);
               // printf("yaw:%f",yaw);
              // printf("gyr_y:      %d\r\n",gyr_y);
 
             PID_control();

                
                temp_pit=rol;

            
            
            /* 在LCD上显示相关数据信息 */
               
        }
        ret_exit = 0;
        break;
        
        default:break;
                
        
    }
}

/**
 * @brief       外部中断初始化程序
 * @param       无
 * @retval      无
 */
void MPU6050_extix_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    MPU6050_INT_GPIO_CLK_ENABLE();                              /* KEY0时钟使能 */


    gpio_init_struct.Pin = MPU6050_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* 下降沿触发 */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(MPU6050_INT_GPIO_PORT, &gpio_init_struct);    /* KEY0配置为下降沿触发中断 */
    
    HAL_NVIC_SetPriority(MPU6050_INT_IRQn, 2, 2);               /* 抢占2，子优先级2 */
    HAL_NVIC_EnableIRQ(MPU6050_INT_IRQn);                       /* 使能中断线15 */

}












