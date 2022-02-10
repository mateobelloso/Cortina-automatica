#ifndef MAIN_H_
#define MAIN_H_

	#include <stm32f103x6.h>
	#include <stdint.h>

	typedef struct
	{
		uint8_t segundos;
		uint8_t minutos;
		uint8_t horas;
	}tiempo;                //Define el tipo de dato tiempo

	#include "reloj.h"
	#include "remoto.h"
	#include "motor.h"
	#include "sensor.h"
	#include "sEOS.h"
	#include "cortina.h"

	void delay_us (uint16_t t);

#endif
