#include "./BSP/ENCODER/encoder.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "stm32f1xx_hal.h"

uint32_t sys_tick_left;
uint32_t sys_tick_right;
void power_encoder(void);
 TIM_HandleTypeDef htim2;

void MX_TIM2_Init(void)
{
  power_encoder();
  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
    HAL_TIM_Encoder_Init(&htim2, &sConfig) ;
  
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
 HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) ;
 
     HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);

}

TIM_HandleTypeDef htim3;

void MX_TIM3_Init(void)
{


  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  HAL_TIM_Encoder_Init(&htim3, &sConfig) ;
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);
  
     HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1);

}

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* tim_encoderHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_encoderHandle->Instance==TIM2)
  {
    ENCODER_TIM2_CH1_GPIO_CLK_ENABLE();
    ENCODER_TIM2_CH2_GPIO_CLK_ENABLE();
    //__HAL_RCC_AFIO_CLK_ENABLE(); 

    GPIO_InitStruct.Pin = ENCODER_TIM2_CH1_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(ENCODER_TIM2_CH1_GPIO_PORT, &GPIO_InitStruct);      

    GPIO_InitStruct.Pin = ENCODER_TIM2_CH2_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(ENCODER_TIM2_CH2_GPIO_PORT, &GPIO_InitStruct);

  }
  if(tim_encoderHandle->Instance==TIM3)
  {
//    __HAL_RCC_AFIO_CLK_ENABLE(); 
//    __HAL_AFIO_REMAP_SWJ_DISABLE(); 
//    __HAL_AFIO_REMAP_TIM3_PARTIAL() ;

    ENCODER_TIM3_CH1_GPIO_CLK_ENABLE();
    ENCODER_TIM3_CH2_GPIO_CLK_ENABLE();
    GPIO_InitStruct.Pin = ENCODER_TIM3_CH1_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ENCODER_TIM3_CH1_GPIO_PORT, &GPIO_InitStruct);
      
    GPIO_InitStruct.Pin = ENCODER_TIM3_CH2_GPIO_PIN;
    HAL_GPIO_Init(ENCODER_TIM3_CH2_GPIO_PORT, &GPIO_InitStruct);


      


  }
}

void power_encoder(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    VCC_ENCODER_TIM2_GPIO_CLK_ENABLE(); 
    GND_ENCODER_TIM2_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin = VCC_ENCODER_TIM2_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(VCC_ENCODER_TIM2_GPIO_PORT, &GPIO_InitStruct);      

    GPIO_InitStruct.Pin = GND_ENCODER_TIM2_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GND_ENCODER_TIM2_GPIO_PORT, &GPIO_InitStruct);
    
    VCC_ENCODER_TIM3_GPIO_CLK_ENABLE(); 
    GND_ENCODER_TIM3_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin = VCC_ENCODER_TIM3_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(VCC_ENCODER_TIM3_GPIO_PORT, &GPIO_InitStruct);      

    GPIO_InitStruct.Pin = GND_ENCODER_TIM3_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GND_ENCODER_TIM3_GPIO_PORT, &GPIO_InitStruct);
    VCC_ENCODER_TIM2(1);
    GND_ENCODER_TIM2(0);
    VCC_ENCODER_TIM3(1);
    GND_ENCODER_TIM3(0);


}



short  Get_Encoder_Leftcounter(void)
{
   short num= (short)__HAL_TIM_GET_COUNTER(&htim2);
    __HAL_TIM_SetCounter(&htim2,0);
//    printf("num:%d\r\n",num);

      return num;
}

short  Get_Encoder_Rightcounter(void)
{
   short num= (short)__HAL_TIM_GET_COUNTER(&htim3);
    __HAL_TIM_SetCounter(&htim3,0);

     return num;
}


short  RightSpeed;
void Read_RightSpeed(short *RightSpeed)
{
//  printf("uwTick%d\r\n",uwTick);

    if((uwTick-sys_tick_right)>=10)
    {

        sys_tick_right=uwTick;
        *RightSpeed=Get_Encoder_Rightcounter(); 

    }else
    {

    
    }

}


short  LeftSpeed;
void Read_LeftSpeed(short*LeftSpeed)
{
        if((uwTick-sys_tick_left)>=10)
    {

        sys_tick_left=uwTick;
        *LeftSpeed=Get_Encoder_Leftcounter(); 

    }else
    {

    
    }

}









