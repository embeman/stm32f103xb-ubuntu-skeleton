#include "stm32f1xx.h"
#include "led.h"

void __attribute__ ((weak)) _init(void)  {}

void RCC_Init()
{
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));

	RCC->CR |= RCC_CR_CSSON;
	
	FLASH->ACR = FLASH_ACR_LATENCY;

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;  // 72 MHz
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // 36 MHz & 72 MHz for Timers
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // 72 MHz
	
	RCC->CFGR &= ~RCC_CFGR_PLLMULL;
	RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;
	RCC->CFGR &= ~RCC_CFGR_USBPRE;
	
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;   //  ADC Prescaler  72 / 6 = 12 MHz
	RCC->CFGR |= RCC_CFGR_PLLSRC;
	RCC->CFGR |= RCC_CFGR_PLLMULL9;
	
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY)) ;
	
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)) ;
}

void delay() 
{
	volatile uint32_t i;
	for (i = 0; i != 1500000; i++) ; // ~ 1 s
}

int main()
{
	RCC_Init();
	led_init();
	
	while(1)
	{	
		led_on();
		delay();
		led_off();
		delay();
	}
}
