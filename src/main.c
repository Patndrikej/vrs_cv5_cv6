#include <stddef.h>
#include "stm32l1xx.h"
#include "vrs_cv5.h"
#include "stdio.h"


int main(void) {
	adcInit();
	initAdcIrq();
	initLed();
	usart_init();

	i=0;

	while (1){

		delayLed(value);
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);

		sprintf(send,"%d",value);
		sendData(send);

		i++;
	}

	 return 0;
}
