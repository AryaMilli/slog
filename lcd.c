#include "stm32f4xx.h"
#include <stdio.h>

void msdelay (unsigned int itime){
	unsigned int i,j;
	for (i=0; i<itime;i++){
		for(j=0;j<1275;j++);
	}
} 

void LCD_command(unsigned char cmd){
	//clearing data lines
	GPIOE -> BSRR = 0xffff << 16;
	GPIOD -> BSRR = 1<< (16+7)|1<< (16+8)|1<< (16+9);
	//rs =0
	GPIOD -> BSRR = 1<< (16+10);
	//rw is gnd thus 0
	if(cmd & 0x01)
						GPIOE->BSRR= 1<<11;
					else
						GPIOE->BSRR= 1<<(16+11);
				if(cmd & 0x02)
						GPIOE->BSRR= 1<<12;
					else
						GPIOE->BSRR= 1<<(16+12);
				if(cmd & 0x04)
						GPIOE->BSRR= 1<<13;
					else
						GPIOE->BSRR= 1<<(16+13);
				if(cmd & 0x08)
						GPIOE->BSRR= 1<<14;
					else
						GPIOE->BSRR= 1<<(16+14);
				if(cmd & 0x10)
						GPIOE->BSRR= 1<<15;
					else
						GPIOE->BSRR= 1<<(16+15);
				if(cmd & 0x20)
						GPIOD->BSRR= 1<<7;
					else
						GPIOD->BSRR= 1<<(16+7);
				if(cmd & 0x40)
						GPIOD->BSRR= 1<<8;
					else
						GPIOD->BSRR= 1<<(16+8);
				if(cmd & 0x80)
						GPIOD->BSRR= 1<<9;
					else
						GPIOD->BSRR= 1<<(16+9);
	//en high
	GPIOH -> BSRR = 1<<1;
	msdelay(10);
	GPIOH -> BSRR = 1<<17;
}

void LCD_data(unsigned char data){
	//clearing data lines
	//GPIOE -> BSRR = 0xffff << 16;
	//GPIOD -> BSRR = 1<< (16+7)|1<< (16+8)|1<< (16+9);
	//rs 1
	GPIOD -> BSRR = 1<<10;
	//rw is gnd
	if(data & 0x01)
				GPIOE->BSRR= 1<<11;
			else
				GPIOE->BSRR= 1<<(16+11);
		if(data & 0x02)
				GPIOE->BSRR= 1<<12;
			else
				GPIOE->BSRR= 1<<(16+12);
		if(data & 0x04)
				GPIOE->BSRR= 1<<13;
			else
				GPIOE->BSRR= 1<<(16+13);
		if(data & 0x08)
				GPIOE->BSRR= 1<<14;
			else
				GPIOE->BSRR= 1<<(16+14);
		if(data & 0x10)
				GPIOE->BSRR= 1<<15;
			else
				GPIOE->BSRR= 1<<(16+15);
		if(data & 0x20)
				GPIOD->BSRR= 1<<7;
			else
				GPIOD->BSRR= 1<<(16+7);
		if(data & 0x40)
				GPIOD->BSRR= 1<<8;
			else
				GPIOD->BSRR= 1<<(16+8);
		if(data & 0x80)
				GPIOD->BSRR= 1<<9;
			else
				GPIOD->BSRR= 1<<(16+9);

	//en high
	GPIOH -> BSRR = 1<<1;
	msdelay(10);
	GPIOH -> BSRR = 1<<17;
}

void LCD_init(){
	LCD_command(0x38);//8 bit mode
	msdelay(10);
	LCD_command(0x0C);//display on cursor off
	msdelay(10);
	LCD_command(0x06);//cursor increment, display shift
	msdelay(10);
	LCD_command(0x01);//clear lcd
	msdelay(10);
	LCD_command(0x80);//set cursor
	msdelay(10);
}

void LCD_write_string(unsigned char *string){
	while(*string){
		LCD_data(*string++);
	}
}
int main(){
	RCC -> AHB1ENR = 1<<3|1<<4|1<<7; //clk enble
	GPIOD -> MODER = 0x154000; //data pins config PED7 to PD9 and rs pin PD10
	GPIOE -> MODER = 0x55400000;//data pins config PE11 to PE15
	GPIOH -> MODER = 0x04; ////PH1 en pin

	while(1){
	LCD_init();
	LCD_write_string("WELCOME");
	msdelay(100);

	LCD_command(0xC0); //second line
	LCD_write_string("WORLD");
	msdelay(100);
	}
	return 0;
}
