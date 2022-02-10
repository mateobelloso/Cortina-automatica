#include "sensor.h"

static uint32_t valor=0;

void delay_us (uint16_t t)  //Funcion que genera un delay de t micro-segundos 
{
   volatile unsigned long l = 0;
   uint16_t i;
   for( i= 0; i < t; i++)
      for(l = 0; l < 6; l++)
  { }
 }

void sensor_init()
{
	RCC->APB2ENR |= (1<<9);
	GPIOA->CRL = 0x44444304;
	GPIOA->BSRR |= (1<<2);
	ADC1->CR2= 1;
	ADC1->SMPR2= (1<<3);
}

void sensor_medir()
{
	ADC1->SQR3=1;
	ADC1->CR2= 1;
	while((ADC1->SR&(1<<1)) == 0);
	valor= ADC1->DR;
}

uint32_t sensor_get_valor()
{
	return valor;
}

void sensor_desactivar()
{
	GPIOA->BRR|= (1<<2);
}
