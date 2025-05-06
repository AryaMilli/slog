#include "stm32f4xx.h"
#include <stdio.h>

int main(){
	RCC -> AHB1ENR =0x0F; //port d clk enabled 
	//d2 d3 pins for button
	//c0 c2 c3 for led
	GPIOC -> MODER = 0x51; //output mode for the pins 
	GPIOD -> MODER = 0x00;
  while(1){
   if(!((GPIOD -> IDR) & (1<<2))){ //check if push button is ON 
	   GPIOC -> BSRR = 1<<0; //turn ON the led 
	 //  msdelay(500);
   }
   else
   {
	   GPIOC -> BSRR = 1<<16; //turn OFF the led 
   }
   if(!((GPIOD -> IDR) & (1<<3))){
  	   GPIOC -> BSRR = 1<<2; // same proce diff led 
  	   //msdelay(500);
   }
   else
   {
	   GPIOC -> BSRR = 1<<18;
   }
  }
	return 0;
}
