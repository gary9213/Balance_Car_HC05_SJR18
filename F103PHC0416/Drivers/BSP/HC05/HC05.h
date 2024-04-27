#ifndef __HC05_H
#define __HC05_H

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/UART_HC05/atk_mw8266d_uart.h"

/******************************************************************************************/


#define HC05_EN_GPIO_PORT                    GPIOB
#define HC05_EN_GPIO_PIN                     GPIO_PIN_0
#define HC05_EN_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0) /* PA口时钟使能 */

#define HC05_STATE_GPIO_PORT                    GPIOB
#define HC05_STATE_GPIO_PIN                     GPIO_PIN_1
#define HC05_STATE_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0) /* PA口时钟使能 */

#define HC05_EN(x)   do{ x ? \
                      HAL_GPIO_WritePin(HC05_EN_GPIO_PORT, HC05_EN_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(HC05_EN_GPIO_PORT, HC05_EN_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)      /* LED0翻转 */

#define HC05_STATE    HAL_GPIO_ReadPin(HC05_STATE_GPIO_PORT,HC05_STATE_GPIO_PIN)

/******************************************************************************************/

void HC05_init(void);



#endif