#include "stm32f4xx.h"
#include <stdio.h>

void msdelay(unsigned int itime){
 unsigned int i,j;
 for (i=0; i<itime;i++){
	 for(j=0;j<1275;j++);
 }
}

int main(){
 while(1){
	RCC -> AHB1ENR = 1 <<1|1 <<2; //port b, c enable clk
	GPIOC -> MODER = 0x51; //output mode pin 0 2 3
	GPIOB -> MODER = 0x05;
	GPIOC -> BSRR = 1<<0;
	GPIOC -> BSRR = 1<<3;
	GPIOC -> BSRR = 1<<2;
	GPIOB -> BSRR = 1<<0;
	GPIOB -> BSRR = 1<<1;
    msdelay(500);
	GPIOC -> BSRR = 1<<16;
	GPIOC -> BSRR = 1<<19;
	GPIOC -> BSRR = 1<<18;
	GPIOB -> BSRR = 1<<16;
	GPIOB -> BSRR = 1<<17;
    msdelay(500);
   }
	return 0;
}
