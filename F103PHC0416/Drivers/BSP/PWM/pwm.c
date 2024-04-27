#include "./BSP/PWM/pwm.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/sys/sys.h"

/**
 ****************************************************************************************************
 * @file        PWM.c
 * @author      
 * @version     V1.0
 * @date        2023-03-28
 * @brief       PWM�������� 
 * @license     

 ****************************************************************************************************
 */


TIM_HandleTypeDef g_tim1_handle;         /* ��ʱ����� */

/**
 * @brief       PWM ��ʼ��, ʵ���Ͼ��ǳ�ʼ����ʱ��
 * @note
 *              ��ʱ����ʱ������APB1 / APB2, ��APB1 / APB2 ��Ƶʱ, ��ʱ��Ƶ���Զ�����
 *              ����, һ�������, �������ж�ʱ����Ƶ��, ����72Mhz ����ϵͳʱ��Ƶ��
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft = ��ʱ������Ƶ��, ��λ: Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void pwmdac_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_pwmdac = {0};

    g_tim1_handle.Instance = PWM_TIMX;                                                /* ��ʱ��1 */
    g_tim1_handle.Init.Prescaler = psc;                                           /* ��ʱ����Ƶ */
    g_tim1_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* ��������ģʽ */
    g_tim1_handle.Init.Period = arr;                                              /* �Զ���װ��ֵ */
    g_tim1_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* ʹ��TIMx_ARR���л��� */
    HAL_TIM_PWM_Init(&g_tim1_handle);                                             /* ��ʼ��PWM */

    timx_oc_pwmdac.OCMode = TIM_OCMODE_PWM1;                                      /* CH1/2 PWMģʽ1 */
    timx_oc_pwmdac.Pulse = 0;                                                     /* ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձ� */
    timx_oc_pwmdac.OCPolarity = TIM_OCPOLARITY_HIGH;                              /* ����Ƚϼ���Ϊ�� */
    HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &timx_oc_pwmdac, TIM_CHANNEL_1);  /* ����TIM1ͨ��1 */
    HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &timx_oc_pwmdac, TIM_CHANNEL_4);  /* ����TIM1ͨ��2 */
    
    HAL_TIM_PWM_Start(&g_tim1_handle, TIM_CHANNEL_1);                             /* ������ʱ��1ͨ��1 */
    HAL_TIM_PWM_Start(&g_tim1_handle, TIM_CHANNEL_4);
}

/**
 * @brief       ��ʱ���ײ�������ʱ��ʹ�ܣ���������
 * @note
 *              �˺����ᱻHAL_TIM_PWM_Init()����
 * @param       htim:��ʱ�����
 * @retval      ��
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef gpio_init_struct;

    if (htim->Instance == PWM_TIMX)
    {
        PWM_TIMX_CLK_ENABLE();                           /* ʹ�ܶ�ʱ��1 */
        __HAL_AFIO_REMAP_TIM1_PARTIAL();                       /* TIM1ͨ�����Ų�����ӳ��ʹ�� */
        PWM_GPIO_CLK_ENABLE();                              /* GPIO ʱ��ʹ�� */


        gpio_init_struct.Pin = PWM_GPIO_PIN| PWM2_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;  //2MHZ
        HAL_GPIO_Init(PWM_GPIO_PORT, &gpio_init_struct);    /* TIMX PWM CHY ����ģʽ���� */

    }
}
