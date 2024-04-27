#include "./BSP/HC05/hc05.h"

uint8_t Fore,Back,Left,Right;
/**
 * @brief       ��ʼ��LED���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void HC05_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    HC05_EN_GPIO_CLK_ENABLE();                                 /* LED0ʱ��ʹ�� */
    HC05_STATE_GPIO_CLK_ENABLE();

    gpio_init_struct.Pin = HC05_EN_GPIO_PIN;                   /* LED0���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(HC05_EN_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED0���� */
    
    HC05_EN(1);
    
    gpio_init_struct.Pin = HC05_STATE_GPIO_PIN;                   /* LED1���� */
        gpio_init_struct.Mode = GPIO_MODE_INPUT;            /* ������� */
    gpio_init_struct.Pull = GPIO_NOPULL;                    /* ���� */
    HAL_GPIO_Init(HC05_STATE_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED1���� */
//    HC05_STATE;
    atk_mw8266d_uart_init(9600);
    
}

void HC05_receive_message(void)
{
    

uint8_t  HC05_re=*atk_mw8266d_uart_rx_get_frame();       /* ��ȡATK-MW8266D UART���յ���һ֡���� */
//uint16_t HC05_len=atk_mw8266d_uart_rx_get_frame_len();   /* ��ȡATK-MW8266D UART���յ���һ֡���ݵĳ��� */
    

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
        atk_mw8266d_uart_rx_restart();             /* ATK-MW8266D UART���¿�ʼ�������� */
//void USART3_IRQHandler(void) 
//{
//	int Bluetooth_data;
//	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)//�����жϱ�־λ����
//	{
//		
//		Bluetooth_data=USART_ReceiveData(USART3);//������յ�����
//	
//		if(Bluetooth_data==0x00)Fore=0,Back=0,Left=0,Right=0;//ɲ
//		else if(Bluetooth_data==0x01)Fore=1,Back=0,Left=0,Right=0;//ǰ
//		else if(Bluetooth_data==0x05)Fore=0,Back=1,Left=0,Right=0;//��
//		else if(Bluetooth_data==0x03)Fore=0,Back=0,Left=1,Right=0;//��
//		else if(Bluetooth_data==0x07)Fore=0,Back=0,Left=0,Right=1;//��
//		else if(Bluetooth_data==0x09)Mode_flag=1;//��������ģʽ
//		else if(Bluetooth_data==0x11)Mode_flag=2;//ѭ������ģʽ
//		else if(Bluetooth_data==0x13)Mode_flag=3;//����ģʽ
//		else Fore=0,Back=0,Left=0,Right=0,Mode_flag=0;//ɲ
//		
//		

//	}
//}

}

    