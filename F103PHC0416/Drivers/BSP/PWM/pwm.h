#ifndef __PWM_H
#define __PWM_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* PWM DAC ���� �� ��ʱ�� ���� */

/* PWMDAC Ĭ����ʹ�� PA8, ��Ӧ�Ķ�ʱ��Ϊ TIM1_CH1, �����Ҫ�޸ĳ�����IO���, ����Ӧ
 * �Ķ�ʱ����ͨ��ҲҪ�����޸�. �����ʵ����������޸�.
 */
#define PWM_GPIO_PORT                    GPIOA
#define PWM_GPIO_PIN                     GPIO_PIN_8
#define PWM_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0) /* PA��ʱ��ʹ�� */

#define PWM_TIMX                         TIM1
#define PWM_TIMX_CHY                     TIM_CHANNEL_1                               /* ͨ��Y,  1<= Y <=4 */
#define PWM_TIMX_CCRX                    PWM_TIMX->CCR1                           /* ͨ��Y������ȽϼĴ��� */
#define PWM_TIMX_CLK_ENABLE()            do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)  /* TIM1 ʱ��ʹ�� */

#define PWM2_GPIO_PORT                    GPIOA
#define PWM2_GPIO_PIN                     GPIO_PIN_11
#define PWM2_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0) /* PA��ʱ��ʹ�� */

#define PWM2_TIMX                         TIM1
#define PWM2_TIMX_CHY                     TIM_CHANNEL_4                               /* ͨ��Y,  1<= Y <=4 */
#define PWM2_TIMX_CCRX                    PWM_TIMX->CCR1                           /* ͨ��Y������ȽϼĴ��� */
#define PWM2_TIMX_CLK_ENABLE()            do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)  /* TIM1 ʱ��ʹ�� */

/******************************************************************************************/

void pwmdac_init(uint16_t arr, uint16_t psc);



#endif
