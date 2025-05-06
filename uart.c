#include "stm32f4xx.h"
#include <stdio.h>

/* void msdelay(unsigned int itime){
	unsigned int i,j;
	for (i=0;i<itime;i++){
		for (j=0;j<1275;j++);
	}
}*/

void msdelay(unsinged int itime){
	unsigned int i,j; 
	for (i=0;i<itime;i++){
		for (j=0;j<1275;j++);
	}
}
void USART3_init(void){
//	RCC ->AHB1ENR = 1 <<2; //port c clk enable
//	GPIOC -> MODER =0xA00000; //AF mode for UART PA10 and PA11
	GPIOC -> AFR[1]=7<<8; //afr for pins 8 to 15 AF7 mode 0111
	GPIOC -> AFR[1]=7<<12;

	USART3 -> CR1 = 0x00; //clear all
	USART3 -> CR1 = 1<<13; //UE enable 14th pin

	USART3 -> BRR = (7<<0)| (24<<4); //setting clk and baud rate 115200 45 Hz

	USART3 -> CR1 = 1<<2; //rx enable
	USART3 -> CR1 = 1<<3; //tx enable
}

void USART3_TxData(char c){
	USART3 -> DR =c; //load the data into data register
	while(!(USART3-> SR & (1<<6))); //wait for TC bit to be 1
}

void USART3_SendString(char *str){
	while(*str){
		USART3_TxData(*str++);
	}
}

uint8_t USART3_RxData(void){
	uint8_t temp;
	while(!((USART3->SR)& (1<<5))); //wait for RX bit to be 1 rxne bit
	temp = USART3->DR;
	return temp;
}

int main(void)
{
    USART3_init(); // Initialize UART2

    // Transmit a message
    char *msg = "Hello, STM32 UART!\r\n";
    while (*msg)
    {
        USART3_TxData(*msg++);
    }

    while (1)
    {
        // Echo received character
        char receivedChar = USART3_RxData();
        USART3_TxData(receivedChar);
    }
}
//int main(){
//	RCC ->AHB1ENR = 1 <<2; //port c clk enable
//	GPIOC -> MODER =0xA00000; //AF mode for UART PA10 and PA11
//	//char receive;
//	USART3_init();
//	while(1){
//		//USART3_TxData('G');
//		USART3_SendString("HELLO");
//    	msdelay(1000);
////		receive = USART3_RxData();
////		USART3_SendString("RECEIVED");
////		USART3_TxData(receive);
////		USART3_SendString("\r\n");
////		msdelay(1000);
//
//		//uint8_t data =USARRT3_RxData();
//	//	USART3_TxData(data);
//	}
//	return 0;
//}
