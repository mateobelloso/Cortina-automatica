#include "remoto.h"

static uint8_t BUFFER_RX[20];
static uint8_t se_envio_comando= 0;

void remoto_init()
{
	RCC->APB2ENR |= 1 << 14;	//Habilita el clk al modulo USART1
	GPIOA->ODR|= 1 << 10;		//Activa el pull up del puerto PA10(RX)
	GPIOA->CRH= 0x444448B4;	//Configura como entrada pull-up al puerto PA10(RX) y como salida al puerto PA9(TX)
	USART1->CR1= 0x202C;	//Activa la recepcion y la interrupcion de recepcion
	USART1->BRR= 7500;	//72MHz/9600bps=7500
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler()	//Interrupcion que se ejecuta cuando se recibe un dato y lo guarda en el buffer
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

uint8_t remoto_get_string_from_buffer(uint8_t * cadena)	//Funcion que retorna el valor almacenado en el buffer a traves del parametro cadena y devuelve la cantidad de caracteres que tiene este
{
	uint8_t i;
	for(i=0;BUFFER_RX[i]!='\0';i++)
	{	
		cadena[i]= BUFFER_RX[i];
	}
	cadena[i]= '\0';
	return i;
}

uint8_t get_se_envio_comando()	//Funcion para acceder al valor de la variable se envio comando
{
	return se_envio_comando;
}

void set_se_envio_comando(uint8_t c)	//Funcion para cambiar el valor de la variable se envio comando
{
	se_envio_comando= c;
}

void checkearBluetooth(uint8_t *porcentaje, tiempo *horaS, tiempo *horaB,uint8_t * cantidad)	//Funcion que chequea el comando que se recibio y en el caso de ser un porcentaje lo retorna a traves de porcentaje. En el caso de ser dos horas las retorna en las variables hora pasadas como parametro
{
	uint8_t cadena[20];
	uint8_t i;
	*cantidad=remoto_get_string_from_buffer(cadena);
	if(*cantidad<=3)
	{
		*porcentaje= 0;
		for(i=0;cadena[i] != '\0';i++)
		{	
			*porcentaje=*porcentaje * 10 + cadena[i] - '0';
		}
	}else
	{
		(*horaS).horas=0;
		(*horaS).minutos=0;
		for(i=0;i<2;i++)
		{
			(*horaS).horas= (*horaS).horas * 10 + cadena[i] - '0';
		}
		for(;i<4;i++)
		{
			(*horaS).minutos= (*horaS).minutos * 10 + cadena[i] - '0';
		}
		(*horaS).segundos= 0;
		(*horaB).horas=0;
		(*horaB).minutos=0;
		for(;i<6;i++)
		{
			(*horaB).horas= (*horaB).horas * 10 + cadena[i] - '0';
		}
		for(;i<8;i++)
		{
			(*horaB).minutos= (*horaB).minutos * 10 + cadena[i] - '0';
		}
		(*horaB).segundos= 0;
	}
}
