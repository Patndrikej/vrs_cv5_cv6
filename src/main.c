#include <stddef.h>
#include "stm32l1xx.h"
#include "vrs_cv5.h"
#include "stdio.h"


int main(void) {
	adcInit();
	initAdcIrq();
	initLed();
	usart_init();
	status=0;



	  while(1){


		  frekvencie();


	  }
	  return 0;
	}
