#ifndef VRS_CV5_H_
#define VRS_CV5_H_

#include "stm32l1xx.h"

extern volatile uint16_t value;
uint16_t Input;
//value from ADC

char send[16];

void initAdcIrq(void);
void usart_init(void);
void ADC1_IRQHandler(void);
void USART_IRQ_init(void);
void initLed(void);
void adcInit(void);
void USART2_IRQHandler(void);
void sendData(char send[]);
void USART2_IRQHandler(void);


char res[10];
char format;

int u;
int odchylka;
int v;
int status;

#endif
