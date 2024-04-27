#include "./BSP/PWM/pwm.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/sys/sys.h"

/**
 ****************************************************************************************************
 * @file        PWM.c
 * @author      
 * @version     V1.0
 * @date        2023-03-28
 * @brief       PWM驱动代码 
 * @license     

 ****************************************************************************************************
 */


TIM_HandleTypeDef g_tim1_handle;         /* 定时器句柄 */

/**
 * @brief       PWM 初始化, 实际上就是初始化定时器
 * @note
 *              定时器的时钟来自APB1 / APB2, 当APB1 / APB2 分频时, 定时器频率自动翻倍
 *              所以, 一般情况下, 我们所有定时器的频率, 都是72Mhz 等于系统时钟频率
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft = 定时器工作频率, 单位: Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void pwmdac_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_pwmdac = {0};

    g_tim1_handle.Instance = PWM_TIMX;                                                /* 定时器1 */
    g_tim1_handle.Init.Prescaler = psc;                                           /* 定时器分频 */
    g_tim1_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* 递增计数模式 */
    g_tim1_handle.Init.Period = arr;                                              /* 自动重装载值 */
    g_tim1_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* 使能TIMx_ARR进行缓冲 */
    HAL_TIM_PWM_Init(&g_tim1_handle);                                             /* 初始化PWM */

    timx_oc_pwmdac.OCMode = TIM_OCMODE_PWM1;                                      /* CH1/2 PWM模式1 */
    timx_oc_pwmdac.Pulse = 0;                                                     /* 设置比较值,此值用来确定占空比 */
    timx_oc_pwmdac.OCPolarity = TIM_OCPOLARITY_HIGH;                              /* 输出比较极性为高 */
    HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &timx_oc_pwmdac, TIM_CHANNEL_1);  /* 配置TIM1通道1 */
    HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &timx_oc_pwmdac, TIM_CHANNEL_4);  /* 配置TIM1通道2 */
    
    HAL_TIM_PWM_Start(&g_tim1_handle, TIM_CHANNEL_1);                             /* 开启定时器1通道1 */
    HAL_TIM_PWM_Start(&g_tim1_handle, TIM_CHANNEL_4);
}

/**
 * @brief       定时器底层驱动，时钟使能，引脚配置
 * @note
 *              此函数会被HAL_TIM_PWM_Init()调用
 * @param       htim:定时器句柄
 * @retval      无
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef gpio_init_struct;

    if (htim->Instance == PWM_TIMX)
    {
        PWM_TIMX_CLK_ENABLE();                           /* 使能定时器1 */
        __HAL_AFIO_REMAP_TIM1_PARTIAL();                       /* TIM1通道引脚部分重映射使能 */
        PWM_GPIO_CLK_ENABLE();                              /* GPIO 时钟使能 */


        gpio_init_struct.Pin = PWM_GPIO_PIN| PWM2_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;  //2MHZ
        HAL_GPIO_Init(PWM_GPIO_PORT, &gpio_init_struct);    /* TIMX PWM CHY 引脚模式设置 */

    }
}
