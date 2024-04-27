#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
//#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"
#include "demo.h"
#include "./BSP/ATK_MD0096/atk_md0096.h"
#include "./BSP/PWM/pwm.h"
#include "./BSP/ENCODER/encoder.h"
#include "./BSP/MOTOR/motor.h"
#include "./BSP/PID/pid.h"
#include "./BSP/UART_HC05/atk_mw8266d_uart.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化为115200 */
    //    led_init();                         /* 初始化LED */
    //key_init();                         /* 初始化按键 */
    mpu6050_run();
    power();
    MOTOR_GPIO_Init();
    PWMout();
    MX_TIM2_Init();
    MX_TIM3_Init();
    OLED_show_mpu6050_data();
}
