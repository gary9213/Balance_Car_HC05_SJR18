#ifndef _ENCODER_H
#define _ENCODER_H
#include "./SYSTEM/sys/sys.h"
/******************************************************************************************/
/* 引脚 定义 */

#define ENCODER_TIM2_CH1_GPIO_PORT                  GPIOA
#define ENCODER_TIM2_CH1_GPIO_PIN                   GPIO_PIN_0
#define ENCODER_TIM2_CH1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); \
                                                        __HAL_RCC_TIM2_CLK_ENABLE(); \
                                                    }while(0)             /* 口时钟使能 */

#define ENCODER_TIM2_CH2_GPIO_PORT                  GPIOA
#define ENCODER_TIM2_CH2_GPIO_PIN                   GPIO_PIN_1
#define ENCODER_TIM2_CH2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); \
                                                        __HAL_RCC_TIM2_CLK_ENABLE(); \
                                                    }while(0)             /* 口时钟使能 */
#define ENCODER_TIM3_CH1_GPIO_PORT                  GPIOA
#define ENCODER_TIM3_CH1_GPIO_PIN                   GPIO_PIN_6
#define ENCODER_TIM3_CH1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); \
                                                        __HAL_RCC_TIM3_CLK_ENABLE(); \
                                                    }while(0)             /* 口时钟使能 */

#define ENCODER_TIM3_CH2_GPIO_PORT                  GPIOA
#define ENCODER_TIM3_CH2_GPIO_PIN                   GPIO_PIN_7
#define ENCODER_TIM3_CH2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); \
                                                        __HAL_RCC_TIM3_CLK_ENABLE(); \
                                                    }while(0)             /* 口时钟使能 */

#define VCC_ENCODER_TIM2_GPIO_PORT                  GPIOA
#define VCC_ENCODER_TIM2_GPIO_PIN                   GPIO_PIN_3
#define VCC_ENCODER_TIM2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); \
                                                    }while(0)             /* 口时钟使能 */
#define GND_ENCODER_TIM2_GPIO_PORT                  GPIOA
#define GND_ENCODER_TIM2_GPIO_PIN                   GPIO_PIN_4
#define GND_ENCODER_TIM2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); \
                                                    }while(0)             /* 口时钟使能 */
#define VCC_ENCODER_TIM3_GPIO_PORT                  GPIOB
#define VCC_ENCODER_TIM3_GPIO_PIN                   GPIO_PIN_14
#define VCC_ENCODER_TIM3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); \
                                                    }while(0)             /* 口时钟使能 */
#define GND_ENCODER_TIM3_GPIO_PORT                  GPIOB
#define GND_ENCODER_TIM3_GPIO_PIN                   GPIO_PIN_15
#define GND_ENCODER_TIM3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); \
                                                    }while(0)             /* 口时钟使能 */
#define VCC_ENCODER_TIM2(x)       do{ x ? \
                                    HAL_GPIO_WritePin(VCC_ENCODER_TIM2_GPIO_PORT, VCC_ENCODER_TIM2_GPIO_PIN, GPIO_PIN_SET) : \
                                    HAL_GPIO_WritePin(VCC_ENCODER_TIM2_GPIO_PORT, VCC_ENCODER_TIM2_GPIO_PIN, GPIO_PIN_RESET); \
                                }while(0)      /*  */

#define GND_ENCODER_TIM2(x)       do{ x ? \
                                    HAL_GPIO_WritePin(GND_ENCODER_TIM2_GPIO_PORT, GND_ENCODER_TIM2_GPIO_PIN, GPIO_PIN_SET) : \
                                    HAL_GPIO_WritePin(GND_ENCODER_TIM2_GPIO_PORT, GND_ENCODER_TIM2_GPIO_PIN, GPIO_PIN_RESET); \
                                }while(0)      /*  */
#define VCC_ENCODER_TIM3(x)       do{ x ? \
                                    HAL_GPIO_WritePin(VCC_ENCODER_TIM3_GPIO_PORT, VCC_ENCODER_TIM3_GPIO_PIN, GPIO_PIN_SET) : \
                                    HAL_GPIO_WritePin(VCC_ENCODER_TIM3_GPIO_PORT, VCC_ENCODER_TIM3_GPIO_PIN, GPIO_PIN_RESET); \
                                }while(0)      /*  */

#define GND_ENCODER_TIM3(x)       do{ x ? \
                                    HAL_GPIO_WritePin(GND_ENCODER_TIM3_GPIO_PORT, GND_ENCODER_TIM3_GPIO_PIN, GPIO_PIN_SET) : \
                                    HAL_GPIO_WritePin(GND_ENCODER_TIM3_GPIO_PORT, GND_ENCODER_TIM3_GPIO_PIN, GPIO_PIN_RESET); \
                                }while(0)      /*  */

                                                    
/******************************************************************************************/

extern TIM_HandleTypeDef htim3;
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void Read_RightSpeed(short*RightSpeed);
void Read_LeftSpeed(short*LeftSpeed);

short  Get_Encoder_Leftcounter(void);
#endif


