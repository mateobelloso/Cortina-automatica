#ifndef CORTINA_H_
#define CORTINA_H_

	#include "main.h"

	#define VALORMAX 411
	#define VALORMIN 356

	void cortina_posicionarCortina(uint8_t dato);
	void cortina_controlSensor(void);
	uint8_t cortina_getCantidadMover(void);

#endif
