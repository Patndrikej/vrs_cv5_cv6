#ifndef VRS_CV5_H_
#define VRS_CV5_H_

#include "stm32l1xx.h"

extern volatile uint16_t value;			//value from ADC

char send[16];

void initAdcIrq(void);
void delayLed(uint32_t value);
void usart_init(void);
void ADC1_IRQHandler(void);
void USART_IRQ_init(void);
void initLed(void);
void adcInit(void);
void USART2_IRQHandler(void);
void sendData(char send[]);

int i;
int value_AD;

#endif
