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

uint8_t remoto_get_string_from_buffer(uint8_t * cadena)
{
	uint8_t i;
	for(i=0;BUFFER_RX[i]!='\0';i++)
	{	
		cadena[i]= BUFFER_RX[i];
	}
	cadena[i]= '\0';
	return i;
}

uint8_t get_se_envio_comando()
{
	return se_envio_comando;
}

void set_se_envio_comando(uint8_t c)
{
	se_envio_comando= c;
}

uint8_t checkearBluetooth(uint8_t *porcentaje, tiempo horaS, tiempo horaB)
{
	uint8_t cadena[20];
	uint8_t cantidad,i;
	cantidad=remoto_get_string_from_buffer(cadena);
	if(cantidad<=3)
	{
		*porcentaje= 0;
		for(i=0;cadena[i] != '\0';i++)
		{	
			*porcentaje=*porcentaje * 10 + cadena[i] - '0';
		}
	}else
	{
		horaS.horas=0;
		horaS.minutos=0;
		for(i=0;i<2;i++)
		{
			horaS.horas= horaS.horas * 10 + cadena[i] - '0';
		}
		for(;i<4;i++)
		{
			horaS.minutos= horaS.minutos * 10 + cadena[i] - '0';
		}
		horaS.segundos= 0;
		horaB.horas=0;
		horaB.minutos=0;
		for(;i<6;i++)
		{
			horaB.horas= horaB.horas * 10 + cadena[i] - '0';
		}
		for(;i<8;i++)
		{
			horaB.minutos= horaB.minutos * 10 + cadena[i] - '0';
		}
		horaB.segundos= 0;
	}
	return(cantidad);
}

   