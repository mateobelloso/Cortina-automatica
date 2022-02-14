#include "sensor.h"

static uint32_t valor;

void delay_us (uint16_t t)  //Funcion que genera un delay de t micro-segundos 
{
   volatile unsigned long l = 0;
   uint16_t i;
   for( i= 0; i < t; i++)
      for(l = 0; l < 6; l++)
  { }
 }

void sensor_init()	//Funcion que inicializa el sensor
{
	RCC->APB2ENR |= (1<<9);	//Habilita el clk en el ADC1
	GPIOA->CRL = 0x44444304;	//Configura como entrada analogica el puerto PA1(ADC1) y como salida el puerto PA2
	GPIOA->BSRR |= (1<<2);	//Pone en 1 al puerto PA2 lo cual le da tension al circuito del sensor
	ADC1->CR2= 1;	//Enciende el ADC1
	ADC1->SMPR2= (1<<3);	//Setea el tiempo de funcionamiento del ADC
}

void sensor_medir()
{
	ADC1->SQR3=1;	//Inicia la medicion
	ADC1->CR2= 1;
	while((ADC1->SR&(1<<1)) == 0);	//Hasta que no se realizo la medicion
	valor= ADC1->DR;	//Guarda el valor leido en la variable valor
}

void sensor_get_valor(uint32_t *medida)	//Funcion que retorna el valor leido
{
	*medida= valor;
}

void sensor_desactivar()	//Funcion que desactiva el sensor
{
	GPIOA->BRR|= (1<<2);
}
