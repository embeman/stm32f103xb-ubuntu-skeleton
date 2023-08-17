#include "led.h"
#include "stm32f1xx.h"




void led_init(){
	// Enable Clock for PORTC
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	GPIOC->CRH |= GPIO_CRH_MODE13;
	GPIOC->CRH &= ~GPIO_CRH_CNF13;
	
	GPIOC->BSRR |= GPIO_BSRR_BS13; // LED OFF (To 3V3)
}

void led_on(){
	GPIOC->BSRR |= GPIO_BSRR_BR13; // LED On (To 0V)
}

void led_off(){
	GPIOC->BSRR |= GPIO_BSRR_BS13; // LED OFF (To 3V3)
}
