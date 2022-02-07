#ifndef REMOTO_H_
#define REMOTO_H_

	#include "main.h"

	void remoto_init(void);
	void USART1_IRQHandler(void);
	uint8_t get_se_envio_comando(void);
	void remoto_get_string_from_buffer(uint8_t * cadena);
	void set_se_envio_comando(uint8_t c);

#endif
