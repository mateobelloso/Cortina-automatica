#include "reloj.h"
   
static tiempo t;

void reloj_init()	//Funcion que inicializa una hora del reloj para probar la simulacion
{
	t.horas=15;
	t.minutos=30;
	t.segundos=0;
}

void reloj_actualizarHora()   //Funcion que actualiza la hora cada 1 seg
{
   if (++t.segundos==60)
   {
      t.segundos=0;
      if (++t.minutos==60)
      {
         t.minutos=0;
         if (++t.horas==24)
         {
            t.horas=0;
         }
      }
   }
}

uint8_t reloj_compararHorario(tiempo *horario)	//Funcion que compara la hora pasada como parametro con la hora actual del sistema
{
	if(((*horario).horas==t.horas) && ((*horario).minutos==t.minutos))
	{
		return 1;	//Si las horas son iguales retorna 1
	}
	return 0;
}
