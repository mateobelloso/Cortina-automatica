
#include "motor.h"

void motor_init()
{
	GPIOB->CRL |= 0x44333444;
	GPIOB->BRR= (1<<3) |(1<<4);
	GPIOB->BSRR= (1<<5);
}

void motor_girar_derecha()
{
	GPIOB->BRR= (1<<4);
	GPIOB->BSRR= (1<<3);
}

void motor_girar_izquierda()
{
	GPIOB->BRR= (1<<3);
	GPIOB->BSRR= (1<<4);
}

void motor_parar()
{
	GPIOB->BRR= (1<<3) |(1<<4);
}
