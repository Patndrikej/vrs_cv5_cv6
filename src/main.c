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
		  if(status == 0) {
			  sprintf(res,"%d.%dV\n\r", (int) ((3.3)*(value/4095.0)),((int)((3.3)*(value/4095.0)*(100)))%(100));
			  sendData(res);

		  }
//-----------------------Blikanie LED ------------------------------------------------------------------------------------
		//  frekvencie();

//-----------------------Zmena formátu ------------------------------------------------------------------------------------
		  		switch(Input) {

		  		   case 'm'  :
		  			 sprintf(res,"%d.%dV\n\r", (int) ((3.3)*(value/4095.0)),((int)((3.3)*(value/4095.0)*(100)))%(100));
		  			 sendData(res);
		  			 status = 1;
		  		      break;

		  		   case '0'  :
		  			 sprintf(res,"%d\n\r",value);
		  			 sendData(res);
		  			 status = 1;
		  		      break;
		  		   default :
		  			   break;
		  		}

//--------------------------------------------------------------------------------------------------------
	  }
	  return 0;
	}
