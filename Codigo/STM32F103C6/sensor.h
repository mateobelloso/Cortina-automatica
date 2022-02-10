#ifndef SENSOR_H_
#define SENSOR_H_

	#include "main.h"


	void sensor_init(void);
	void sensor_medir(void);
	void sensor_get_valor(uint32_t *medida);
	void sensor_desactivar(void);

#endif
