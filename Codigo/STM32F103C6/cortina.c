#include "cortina.h"

static uint8_t cantidadMover;
static uint8_t porcentajeCortinaCerrada=30;



void cortina_posicionarCortina(uint8_t porcentaje)
{
	if(porcentaje<porcentajeCortinaCerrada)
	{
		cantidadMover=porcentajeCortinaCerrada - porcentaje;
		porcentajeCortinaCerrada= porcentaje;
		motor_girar_derecha();      //Abrir la cortina (dato-porcentaje), x cantidad de porcentaje que equivale a x segundos para la derecha   
	}else
	{
		cantidadMover=porcentaje - porcentajeCortinaCerrada;
		porcentajeCortinaCerrada= porcentaje;
		motor_girar_izquierda();	//Cerra la cortina (dato-porcentaje), x cantidad de porcentaje que equivale a girar x segundos para la izquierda
	}
}

void cortina_controlSensor()
{
	static uint32_t medida;
	sensor_medir();
	delay_us(100);
	sensor_get_valor(&medida);
	if((medida>=356) && (medida<=411))	//Si estoy en el valor deseado detengo la cortina
	{
		motor_parar();
	}else
	{
		if(medida>VALORMAX)	//Si el valor leido por el sensor es mayor que el valor MAX significa que la habitacion esta mas oscura de lo que se quiere
		{
			if(porcentajeCortinaCerrada!=0)	//Chequea que la cortina no este abierta completamente
			{
				motor_girar_derecha();
				porcentajeCortinaCerrada--;
			}
		}else	//Caso contrario el valor leido es menor que el valor MIN lo que significa que la habitacion tiene mas luz de la deseada
		{
			if(porcentajeCortinaCerrada != 100)	//Chequea que la cortina no este cerrada completamente
			{
				motor_girar_izquierda();
				porcentajeCortinaCerrada++;
			}
		}
	}
}
	  
uint8_t cortina_getCantidadMover()
{	     
	return cantidadMover;
}

