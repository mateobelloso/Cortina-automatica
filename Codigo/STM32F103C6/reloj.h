#ifndef RELOJ_H_
#define RELOJ_H_

	#include "main.h"

	typedef struct
	{
		uint8_t segundos;
		uint8_t minutos;
		uint8_t horas;
	}tiempo2;                //Define el tipo de dato tiempo

	void reloj_init(void);
	void reloj_actualizarHora(void);
	uint8_t reloj_compararHorario(tiempo *horario);

#endif
