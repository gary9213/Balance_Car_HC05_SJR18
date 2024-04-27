#include "./BSP/MOTOR/motor.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/sys/sys.h"
#include "./BSP/PWM/pwm.h"
#include "./SYSTEM/usart/usart.h"
extern TIM_HandleTypeDef g_tim1_handle;


void MOTOR_GPIO_Init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    MOTOR_AIN1_GPIO_CLK_ENABLE();
    MOTOR_AIN2_GPIO_CLK_ENABLE();

    gpio_init_struct.Pin = MOTOR_AIN1_GPIO_PIN;                   /* Motorleft_PINA引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(MOTOR_AIN1_GPIO_PORT , &gpio_init_struct);       /* 初始化Motorleft_PINA引脚 */

    gpio_init_struct.Pin = MOTOR_AIN2_GPIO_PIN;                   /* Motorleft_PINA引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(MOTOR_AIN2_GPIO_PORT , &gpio_init_struct);       /* 初始化Motorleft_PINA引脚 */
    
    MOTOR_BIN1_GPIO_CLK_ENABLE();
    MOTOR_BIN2_GPIO_CLK_ENABLE();
    gpio_init_struct.Pin = MOTOR_BIN1_GPIO_PIN;                   /* Motorleft_PINA引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(MOTOR_BIN1_GPIO_PORT , &gpio_init_struct);       /* 初始化Motorleft_PINA引脚 */

    gpio_init_struct.Pin = MOTOR_BIN2_GPIO_PIN;                   /* Motorleft_PINA引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(MOTOR_BIN2_GPIO_PORT , &gpio_init_struct);       /* 初始化Motorleft_PINA引脚 */
    
    
    MOTOR_AIN1(1);
    MOTOR_AIN2(0);
    MOTOR_BIN1(1);
    MOTOR_BIN2(0);
}

int PWM_MAX=7200;
int PWM_MIN=-7200;

/*限幅函数*/
void Limit(int *motoA,int *motoB)
{
	if(*motoA>PWM_MAX)
        *motoA=PWM_MAX;
	if(*motoA<PWM_MIN)
        *motoA=PWM_MIN;
	
	if(*motoB>PWM_MAX)
        *motoB=PWM_MAX;
	if(*motoB<PWM_MIN)
        *motoB=PWM_MIN;
}

/*绝对值函数*/
int GFP_abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}


uint16_t out;
/*赋值函数*/
/*入口参数：PID运算完成后的最终PWM值*/
void Load(int moto1,int moto2)//moto1=-200：反转200个脉冲
{
    if(moto1>0)
    {
       MOTOR_AIN1(0);
       MOTOR_AIN2(1);
    }else
    {
       MOTOR_AIN1(1);
       MOTOR_AIN2(0);
    }
   out =GFP_abs(moto1);//;
    __HAL_TIM_SET_COMPARE(&g_tim1_handle, TIM_CHANNEL_4,out);

    if(moto2>0)
    {
       MOTOR_BIN1(0);
       MOTOR_BIN2(1);
    }else
    {
       MOTOR_BIN1(1);
       MOTOR_BIN2(0);
    }
   out =GFP_abs(moto2);//;290

    __HAL_TIM_SET_COMPARE(&g_tim1_handle, TIM_CHANNEL_1,out);


}
