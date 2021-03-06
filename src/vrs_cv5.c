#include "vrs_cv5.h"

volatile uint16_t value;			//value from ADC

void initAdcIrq(void) // Preru�enie z prevodn�ka
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = ADC1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE); // povolenie preru�enia
	ADC_ITConfig(ADC1, ADC_IT_OVR, ENABLE);
}


void initLed(void) //inicializ�cia LED di�dy
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitTypeDef      GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void adcInit(void) // nastavenie perif�ri�
{
  GPIO_InitTypeDef      GPIO_InitStructure;
  ADC_InitTypeDef       ADC_InitStructure;

  /* Configure ADCx Channel 2 as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable the HSI oscillator */
  RCC_HSICmd(ENABLE);
  /* Check that HSI oscillator is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

  /* Enable ADC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);

  /* ADC1 configuration */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADCx regular channel8 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_384Cycles);

  /* Enable the ADC */
  ADC_Cmd(ADC1, ENABLE);

  /* Wait until the ADC1 is ready */
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
  {
  }

  ADC_SoftwareStartConv(ADC1);
}



void ADC1_IRQHandler(void)
{
	value = ADC1->DR;
}


void USART2_IRQHandler(void){
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		Input = USART_ReceiveData(USART2); // set Input

    }
}

void frekvencie() // Preroben� cvi�enie 4
{
	v = 50000;

	if(( value < 3655 + odchylka) && ( value > 3655 - odchylka )) {
			  v = 50000;

		  }else if(( value < 3459 + odchylka ) && ( value > 3459 - odchylka )) {
			  v = 100000;

		  }else if(( value < 2914 + odchylka  ) && ( value > 2914 - odchylka )) {
			  v = 150000;

		  }else if(( value < 2507 + odchylka  ) && ( value > 2007 - odchylka )) {
			  v = 200000;

		  }else if(( value < 2070 + odchylka ) && ( value > 3240 - odchylka )) {
			  v = 250000;

		  }else if(( value < 1700 + odchylka  ) && ( value > 1700 - odchylka )) {
			  v = 300000;
		  }

		  GPIO_SetBits(GPIOA, GPIO_Pin_5);
		  delay_for_led(v);

		  GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		  delay_for_led(v);

}

void delay_for_led(int value_frek){ // Delay
	for(int j=0;j<=value;j++){}
}


void usart_init()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

		GPIO_InitTypeDef GPIO_usrt;

		//Set GPIO pre TX a RX
		GPIO_usrt.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_usrt.GPIO_Mode = GPIO_Mode_AF;
		GPIO_usrt.GPIO_OType = GPIO_OType_PP;
		GPIO_usrt.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_usrt.GPIO_Speed = GPIO_Speed_40MHz;

		GPIO_Init(GPIOA,&GPIO_usrt);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

		//Nastavenie USART2
		USART_InitTypeDef USART_InitStructure;
		USART_InitStructure.USART_BaudRate = 9600;
		//USART_InitStructure.USART_BaudRate = 9600*2;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART2, &USART_InitStructure);

		  /* Enable the USARTx Interrupt */
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		//interrupt
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

		USART_Cmd(USART2, ENABLE);

}

void sendData(char *res){ // Posielanie d�t
	int index =0;
	while(res[index] != '\0')
	{
		USART_SendData(USART2, res[index]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		index++;
	}
	USART_SendData(USART2,' ');
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}





