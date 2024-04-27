#include "./BSP/HC05/hc05.h"

uint8_t Fore,Back,Left,Right;
/**
 * @brief       初始化LED相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void HC05_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    HC05_EN_GPIO_CLK_ENABLE();                                 /* LED0时钟使能 */
    HC05_STATE_GPIO_CLK_ENABLE();

    gpio_init_struct.Pin = HC05_EN_GPIO_PIN;                   /* LED0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(HC05_EN_GPIO_PORT, &gpio_init_struct);       /* 初始化LED0引脚 */
    
    HC05_EN(1);
    
    gpio_init_struct.Pin = HC05_STATE_GPIO_PIN;                   /* LED1引脚 */
        gpio_init_struct.Mode = GPIO_MODE_INPUT;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                    /* 上拉 */
    HAL_GPIO_Init(HC05_STATE_GPIO_PORT, &gpio_init_struct);       /* 初始化LED1引脚 */
//    HC05_STATE;
    atk_mw8266d_uart_init(9600);
    
}

void HC05_receive_message(void)
{
    

uint8_t  HC05_re=*atk_mw8266d_uart_rx_get_frame();       /* 获取ATK-MW8266D UART接收到的一帧数据 */
//uint16_t HC05_len=atk_mw8266d_uart_rx_get_frame_len();   /* 获取ATK-MW8266D UART接收到的一帧数据的长度 */
    

    switch(HC05_re)
    {
        case 'q':Fore=1,Back=0,Left=0,Right=0;
            break;
        case 'w':Fore=0,Back=0,Left=0,Right=0;
            break;
        case 'e':Fore=0,Back=1,Left=0,Right=0;
            break;
        case 'r':Fore=0,Back=0,Left=0,Right=0;
            break;

        case 't':Fore=0,Back=0,Left=1,Right=0;
            break;

        case 'y':Fore=0,Back=0,Left=0,Right=0;
            break;
        case 'u':Fore=0,Back=0,Left=0,Right=1;
            break;

        case 'i':Fore=0,Back=0,Left=0,Right=0;
            break;

    }
        atk_mw8266d_uart_rx_restart();             /* ATK-MW8266D UART重新开始接收数据 */
//void USART3_IRQHandler(void) 
//{
//	int Bluetooth_data;
//	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)//接收中断标志位拉高
//	{
//		
//		Bluetooth_data=USART_ReceiveData(USART3);//保存接收的数据
//	
//		if(Bluetooth_data==0x00)Fore=0,Back=0,Left=0,Right=0;//刹
//		else if(Bluetooth_data==0x01)Fore=1,Back=0,Left=0,Right=0;//前
//		else if(Bluetooth_data==0x05)Fore=0,Back=1,Left=0,Right=0;//后
//		else if(Bluetooth_data==0x03)Fore=0,Back=0,Left=1,Right=0;//左
//		else if(Bluetooth_data==0x07)Fore=0,Back=0,Left=0,Right=1;//右
//		else if(Bluetooth_data==0x09)Mode_flag=1;//蓝牙控制模式
//		else if(Bluetooth_data==0x11)Mode_flag=2;//循迹控制模式
//		else if(Bluetooth_data==0x13)Mode_flag=3;//避障模式
//		else Fore=0,Back=0,Left=0,Right=0,Mode_flag=0;//刹
//		
//		

//	}
//}

}

    