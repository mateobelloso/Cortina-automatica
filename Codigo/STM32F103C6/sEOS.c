#include "sEOS.h"

static uint8_t automatico=0; //Variable que indica si el modo automatico esta activado cambiado por el bluetooth

//Flags que modifica el bluetooth
static uint8_t flag100ms=0;

static uint8_t flag_posicionarCortina=0;      //flag que indica si el usuario desea posicionar la cortina en un valor

//Verifica si la cortina esta girando
static uint8_t flag_cortinaLibre=1;

static uint8_t flag_actualizarHora=0;	//Flag para actulizar la hora
static uint8_t contadorReloj=0;	//Contador para controlar cuando activar el flag de la tarea del reloj

static uint8_t flag_cortinaCerrada=1;	//Flag que indica que la cortina esta cerrada totalmente en modo automatico

static uint8_t porcentaje;	//Variable que va a contener el porcentaje deseado que ingreso el usuario
static tiempo horaSubir,horaBajar;	//Variables que almacenan los horarios ingresados por los usuarios

static uint8_t contadorCortinaOcupada=0;	//Contador que cuenta el tiempo de desplazamiento de la cortina


//cantidad de caracteres recibidos por la funcion checkear bluetooth
static uint8_t cantidad=0;

void sEOS_SCH_Tareas()	//Planificador de las tareas. esta funcion chequea si pasaron 0.5 segundos 
{
	if(++contadorReloj==10)			//Contador suma 1 cada 100 ms, al llegar a 5 checkea si tiene alguna tarea pendiente
	{
		flag_actualizarHora=1;
		contadorReloj=0;
	}
	flag100ms= 1;
}	

void sEOS_Dispatch_Tareas()	//Dispatcher de tareas. esta funcion chequea los flags de las tareas y si estan en alto las ejecuta y resetea sus flags 
{
	if(flag_actualizarHora)
	{
		reloj_actualizarHora();
		flag_actualizarHora= 0;
	}
	if((flag_cortinaLibre)&&(flag100ms))
	{
		flag100ms= 0;
		if(get_se_envio_comando()) //Checkea el bluetooth si tiene alguna orden pendiente
		{
			checkearBluetooth(&porcentaje,&horaSubir,&horaBajar,&cantidad);
			if(cantidad<=3)
			{
				automatico=0;
				flag_posicionarCortina=1;
			}
			else
			{
				automatico=1;
				flag_posicionarCortina=0;
			}
			set_se_envio_comando(0);
		}
		if (automatico)	// modo automatico
		{
			if(flag_cortinaCerrada)	//Si la cortina esta cerrada al 100 por el horario tengo que esperar al horario programado para subir la cortina
			{
				if(reloj_compararHorario(&horaSubir))	//Si es el horario de subir la cortina la subo
				{
					cortina_posicionarCortina(0);
					flag_cortinaLibre= 0;
					flag_cortinaCerrada= 0;
				}
			}else
			{
				if(reloj_compararHorario(&horaBajar))	//Si es el horario programado de bajada bajo la cortina
				{
					cortina_posicionarCortina(100);
					flag_cortinaLibre= 0;
					flag_cortinaCerrada= 1;
				}else
				{	//En el caso que todavia no sea el horario, se mantiene la luz deseada en la habitacion con el sensor
					cortina_controlSensor();	
				}
			}
		}
		if(!automatico)	//Modo Manual
		{
			if (flag_posicionarCortina)	// Posicionar cortina
			{
				cortina_posicionarCortina(porcentaje); //Funcion que posiciona la cortina un porcentaje dado por el usuario y queda fija
				flag_cortinaLibre=0;
				flag_posicionarCortina= 0;
			}
		}
	}else
	{
		if(flag100ms)
		{
			flag100ms=0;
			if(++contadorCortinaOcupada==cortina_getCantidadMover())
			{ //Cuando la cortina esta girando solo verifica cuando debe parar ignorando las demas solicitudes
				motor_parar();
				flag_cortinaLibre=1;
				contadorCortinaOcupada=0;
			}
		}
	}
}

void SysTick_Handler()	//Interrupcion que ocurre cada 100 ms
{
	sEOS_SCH_Tareas();	//Ejecuta el planificador de tareas
}
