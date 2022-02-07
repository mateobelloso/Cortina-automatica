#include "remoto.h"

static uint8_t BUFFER_RX[20];
static uint8_t se_envio_comando= 0;

void remoto_init()
{
	RCC->APB2ENR |= 1 << 14;
	GPIOA->ODR|= 1 << 10;
	GPIOA->CRH= 0x444448B4;
	USART1->CR1= 0x202C;
	USART1->BRR= 7500;	//72MHz/9600bps=7500
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler()
{
	static uint8_t i= 0;
	BUFFER_RX[i]= USART1->DR;
	if(BUFFER_RX[i]=='\r')
	{
		BUFFER_RX[i]= 0;
		se_envio_comando= 1;
		i= 0;
	}else
	{
		i++;
	}
}

void remoto_get_string_from_buffer(uint8_t * cadena)
{
	uint8_t i;
	for(i=0;BUFFER_RX[i]!='\0';i++)
	{
		cadena[i]= BUFFER_RX[i];
	}
	cadena[i]= '\0';
}

uint8_t get_se_envio_comando()
{
	return se_envio_comando;
}

void set_se_envio_comando(uint8_t c)
{
	se_envio_comando= c;
}
