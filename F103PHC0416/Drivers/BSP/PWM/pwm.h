#ifndef __PWM_H
#define __PWM_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* PWM DAC 引脚 和 定时器 定义 */

/* PWMDAC 默认是使用 PA8, 对应的定时器为 TIM1_CH1, 如果你要修改成其他IO输出, 则相应
 * 的定时器及通道也要进行修改. 请根据实际情况进行修改.
 */
#define PWM_GPIO_PORT                    GPIOA
#define PWM_GPIO_PIN                     GPIO_PIN_8
#define PWM_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0) /* PA口时钟使能 */

#define PWM_TIMX                         TIM1
#define PWM_TIMX_CHY                     TIM_CHANNEL_1                               /* 通道Y,  1<= Y <=4 */
#define PWM_TIMX_CCRX                    PWM_TIMX->CCR1                           /* 通道Y的输出比较寄存器 */
#define PWM_TIMX_CLK_ENABLE()            do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)  /* TIM1 时钟使能 */

#define PWM2_GPIO_PORT                    GPIOA
#define PWM2_GPIO_PIN                     GPIO_PIN_11
#define PWM2_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0) /* PA口时钟使能 */

#define PWM2_TIMX                         TIM1
#define PWM2_TIMX_CHY                     TIM_CHANNEL_4                               /* 通道Y,  1<= Y <=4 */
#define PWM2_TIMX_CCRX                    PWM_TIMX->CCR1                           /* 通道Y的输出比较寄存器 */
#define PWM2_TIMX_CLK_ENABLE()            do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)  /* TIM1 时钟使能 */

/******************************************************************************************/

void pwmdac_init(uint16_t arr, uint16_t psc);



#endif
