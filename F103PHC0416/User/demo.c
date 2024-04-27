#include "demo.h"
#include "./SYSTEM/sys/sys.h"
#include "./BSP/ATK_MS6050/atk_ms6050.h"
#include "./BSP/ATK_MS6050/eMPL/inv_mpu.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/EXTI/exti.h"
#include "./BSP/ATK_MD0096/atk_md0096.h"
#include "./BSP/PWM/pwm.h"
#include "./BSP/PID/pid.h"
extern uint8_t ret_exit;

extern float pit, rol, yaw;
extern int16_t acc_x, acc_y, acc_z;
extern int16_t gyr_x, gyr_y, gyr_z;
extern int16_t temp;
extern float temp_pit;
uint32_t shi,fen;
int64_t temp_pit2;





void OLED_show_mpu6050_data()
{

    atk_md0096_init();
    atk_md0096_oled_show_string(0, 0, ATK_MD0096_OLED_FONT_SIZE_12, "pit:", ATK_MD0096_OLED_SHOW_MODE_NORMAL);
    //atk_md0096_oled_show_num(0, 12, ATK_MD0096_OLED_FONT_SIZE_12, 22, 2, ATK_MD0096_OLED_SHOW_MODE_NORMAL);
    
    atk_md0096_oled_update();
    
    
    
      
        while (1)
    {


        /* ATK-MD0096模块OLED显示字符串 */
        atk_md0096_oled_show_string(0, 0, ATK_MD0096_OLED_FONT_SIZE_12, "pit:", ATK_MD0096_OLED_SHOW_MODE_NORMAL);
        if(temp_pit<0)
        {
            atk_md0096_oled_show_string(24, 0, ATK_MD0096_OLED_FONT_SIZE_12, "-", ATK_MD0096_OLED_SHOW_MODE_NORMAL);
            temp_pit=-temp_pit;
        }else
        {
            atk_md0096_oled_show_string(24, 0, ATK_MD0096_OLED_FONT_SIZE_12, "+", ATK_MD0096_OLED_SHOW_MODE_NORMAL);
        
        }
        temp_pit2=temp_pit*1000000.0;
        shi=temp_pit2/1000000;
        fen=temp_pit2%1000000;
        atk_md0096_oled_show_num(30, 0, ATK_MD0096_OLED_FONT_SIZE_12, (shi), 2, ATK_MD0096_OLED_SHOW_MODE_NORMAL);
        atk_md0096_oled_show_string(42, 0, ATK_MD0096_OLED_FONT_SIZE_12, ".", ATK_MD0096_OLED_SHOW_MODE_NORMAL);
        atk_md0096_oled_show_num(48, 0, ATK_MD0096_OLED_FONT_SIZE_12, (fen), 6, ATK_MD0096_OLED_SHOW_MODE_NORMAL);
        
        /* 更新显存至ATK-MD0096模块 */
        atk_md0096_oled_update();
        

    }

}


/**
 * @brief       例程演示入口函数
 * @param       无
 * @retval      无
 */
void  mpu6050_run(void)
{
   uint8_t ret_init; 
    
    /* 初始化ATK-MS6050 */
    ret_init+= atk_ms6050_init();
    if (ret_init != 0)
    {
        printf("ATK-MS6050 init failed!\r\n");
        atk_md0096_oled_show_string(24, 8, ATK_MD0096_OLED_FONT_SIZE_12, "ATK-MS6050 failed!\r\n", ATK_MD0096_OLED_SHOW_MODE_NORMAL);
        atk_md0096_oled_update();
    }

    /* 初始化ATK-MS6050 DMP */
    ret_init = atk_ms6050_dmp_init();
    if (ret_init != 0)
    {
        printf("ATK-MS6050 DMP init failed!\r\n");
        atk_md0096_oled_show_string(48, 16, ATK_MD0096_OLED_FONT_SIZE_12, "DMP  failed!\r\n", ATK_MD0096_OLED_SHOW_MODE_NORMAL);
        atk_md0096_oled_update();
    }

    PID_ParaInit();
    MPU6050_extix_init();
    
}


extern TIM_HandleTypeDef g_tim1_handle;

void PWMout(void)
{
    pwmdac_init(7200-1, 0);
    
    
  //__HAL_TIM_SET_COMPARE(&g_tim1_handle, TIM_CHANNEL_1, 2000);
//     __HAL_TIM_SET_COMPARE(&g_tim1_handle, TIM_CHANNEL_4, 544);
    

     

    
}

void power(void)
{
        GPIO_InitTypeDef gpio_init_struct; //vcc gnd tb6612

//        __HAL_RCC_GPIOA_CLK_ENABLE(); 
//        gpio_init_struct.Pin = GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0;
//        gpio_init_struct.Mode =GPIO_MODE_OUTPUT_PP;
//        gpio_init_struct.Pull = GPIO_PULLUP;
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;  
//        HAL_GPIO_Init(GPIOA, &gpio_init_struct); 
//    
//        gpio_init_struct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_3;
//        gpio_init_struct.Pull =  GPIO_PULLUP ;
//        HAL_GPIO_Init(GPIOA, &gpio_init_struct); 
//        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, GPIO_PIN_SET) ;
//        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_3, GPIO_PIN_RESET) ;
    
            __HAL_RCC_GPIOB_CLK_ENABLE(); 
        gpio_init_struct.Pin = GPIO_PIN_0;
        gpio_init_struct.Mode =GPIO_MODE_OUTPUT_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;  
        HAL_GPIO_Init(GPIOB, &gpio_init_struct); 
    
        gpio_init_struct.Pin = GPIO_PIN_1;
        gpio_init_struct.Pull =  GPIO_PULLUP ;
        HAL_GPIO_Init(GPIOB, &gpio_init_struct); 

       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET) ;
       HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_RESET) ;
}


