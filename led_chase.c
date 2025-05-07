#include "stm32f4xx.h"

void msdelay(unsigned int itime){
	unsigned int i,j;
	for (i=0; i<itime; i++){
		for(j=0;j<1275;j++);
	}
}

int main(void){
	// Enable clocks for GPIOB and GPIOC
	RCC->AHB1ENR |= (1 << 1) | (1 << 2);  // GPIOB, GPIOC

	// Configure PC0, PC2, PC3 as output
	GPIOC->MODER |= (1 << 0) | (1 << 4) | (1 << 6);  // PC0,2,3

	// Configure PB0, PB1 as output
	GPIOB->MODER |= (1 << 0) | (1 << 2);  // PB0, PB1

	while(1){
		// PC0
		GPIOC->BSRR = (1 << 0);       // ON
		msdelay(300);
		GPIOC->BSRR = (1 << (0 + 16)); // OFF

		// PC2
		GPIOC->BSRR = (1 << 2);
		msdelay(300);
		GPIOC->BSRR = (1 << (2 + 16));

		// PC3
		GPIOC->BSRR = (1 << 3);
		msdelay(300);
		GPIOC->BSRR = (1 << (3 + 16));

		// PB0
		GPIOB->BSRR = (1 << 0);
		msdelay(300);
		GPIOB->BSRR = (1 << (0 + 16));

		// PB1
		GPIOB->BSRR = (1 << 1);
		msdelay(300);
		GPIOB->BSRR = (1 << (1 + 16));
	}
}
