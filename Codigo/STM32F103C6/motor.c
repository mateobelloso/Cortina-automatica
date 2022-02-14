
#include "motor.h"

void motor_init()	//Funcion que inicializa los puertos que se conectan al driver del motor
{
	GPIOB->CRL |= 0x44333444;	//Configura los puertos PA3, PA4 y PA5 como salida
	GPIOB->BRR= (1<<3) |(1<<4);	//Pone en cero los puertos PA3 y PA4
	GPIOB->BSRR= (1<<5);	//Pone en 1 el puerto PA5
}

void motor_girar_derecha()	//Funcion que hace girar hacia la derecha el motor
{
	GPIOB->BRR= (1<<4);
	GPIOB->BSRR= (1<<3);
}

void motor_girar_izquierda()	//Funcion que hace girar hacia la izquierda el motor
{
	GPIOB->BRR= (1<<3);
	GPIOB->BSRR= (1<<4);
}

void motor_parar()	//Funcion que detiene el motor
{
	GPIOB->BRR= (1<<3) |(1<<4);
}
