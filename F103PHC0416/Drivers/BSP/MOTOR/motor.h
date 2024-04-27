#ifndef _MOTOR_H
#define _MOTOR_H
#include "./SYSTEM/sys/sys.h"
/* 引脚定义 */
#define MOTOR_AIN1_GPIO_PORT                          GPIOA
#define MOTOR_AIN1_GPIO_PIN                             GPIO_PIN_2
#define  MOTOR_AIN1_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOA_CLK_ENABLE();   \
                                                   }while(0)   /* PA口时钟使能 */

#define MOTOR_AIN2_GPIO_PORT                          GPIOA
#define MOTOR_AIN2_GPIO_PIN                             GPIO_PIN_3
#define  MOTOR_AIN2_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOA_CLK_ENABLE();   \
                                                   }while(0)   /* PA口时钟使能 */
#define MOTOR_BIN1_GPIO_PORT                          GPIOA
#define MOTOR_BIN1_GPIO_PIN                             GPIO_PIN_4
#define  MOTOR_BIN1_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOA_CLK_ENABLE();   \
                                                   }while(0)   /* PA口时钟使能 */
#define MOTOR_BIN2_GPIO_PORT                          GPIOA
#define MOTOR_BIN2_GPIO_PIN                             GPIO_PIN_5
#define  MOTOR_BIN2_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOA_CLK_ENABLE();   \
                                                   }while(0)   /* PA口时钟使能 */
/* IO操作 */
#define MOTOR_AIN1(x)                   do{ x ?                                                                                             \
                                                    HAL_GPIO_WritePin( MOTOR_AIN1_GPIO_PORT, MOTOR_AIN1_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin( MOTOR_AIN1_GPIO_PORT, MOTOR_AIN1_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)

#define MOTOR_AIN2(x)                   do{ x ?                                                                                             \
                                                    HAL_GPIO_WritePin( MOTOR_AIN2_GPIO_PORT, MOTOR_AIN2_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin( MOTOR_AIN2_GPIO_PORT, MOTOR_AIN2_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)
#define MOTOR_BIN1(x)                   do{ x ?                                                                                             \
                                                    HAL_GPIO_WritePin( MOTOR_BIN1_GPIO_PORT, MOTOR_BIN1_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin( MOTOR_BIN1_GPIO_PORT, MOTOR_BIN1_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)
#define MOTOR_BIN2(x)                   do{ x ?                                                                                             \
                                                    HAL_GPIO_WritePin( MOTOR_BIN2_GPIO_PORT, MOTOR_BIN2_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin( MOTOR_BIN2_GPIO_PORT, MOTOR_BIN2_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)
void Limit(int *motoA,int *motoB);
int GFP_abs(int p);
void MOTOR_GPIO_Init(void);
void Load(int moto1,int moto2);
#endif

