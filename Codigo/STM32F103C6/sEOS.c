

static unint8_t automatico=0; //Variable que indica si el modo automatico esta activado cambiado por el bluetooth

//Flags que modifica el bluetooth
static uint8_t flag_bluetooth=0;

s
tatic uint8_t flag_posicionarCortina=0;      //flag que indica si el usuario desea posicionar la cortina en un valor
static uint8_t flag_setearAutomatico=0;    //flag que indica si el usuario desea variar la cortina, cambiado por bluetooth

//flag que verifica que si se cumplio la hora de bajar la cortina
static uint8_t flag_cortinaBajar=0;

//Verifica si la cortina esta girando
static uint8_t flag_cortinaLibre=1;
static uint8_t flag_cortinaOcupada=0;


//cantidad de caracteres recibidos por la funcion checkear bluetooth
static uint8_t cantidad=0;

void sEOS_SCH_Tareas()	//Planificador de las tareas. esta funcion chequea si pasaron 0.5 segundos 
{
	if(++contador==1)			//Contador suma 1 cada 100 ms, al llegar a 5 checkea si tiene alguna tarea pendiente
	 {
	    sEOS_Dispatch_Tareas();
	     contador=0;
	 }
}	

void sEOS_Dispatch_Tareas()	//Dispatcher de tareas. esta funcion chequea los flags de las tareas y si estan en alto las ejecuta y resetea sus flags 
{
	 if(flag_cortinaLibre){
	    
	 
	 if(flag_bluetooth) //Checkea el bluetooth si tiene alguna orden pendiente
	  {
	      cantidad=checkearBluethooth(&dato);
	      if(cantidad==3){
			   automatico=0;
	       }
	       else{
			ho
		  }
	  }
	    
	if (Automatico)	// modo automatico
	{  
		  if(detectarHoraAutomatico()) //Llamar a una funcion que realice esta comparacion
			checkearSensorLux();//Checkear el sensor para comprobar si se debe bajar o subir la cortina segun el nivel de luz
		 // if(cortinaBaja==0)		//cortinaBaja puede ser una interrupcion que te setea el flag para bajar la cortina?????
		  //   {
		//	   bajarCortina();  //bajar cortina a 0%
		//	   cortinaBaja=1;
	//		}
	}
	else {//Modo Manual
	      
	if (flag_posicionarCortina)	// Posicionar cortina
	{
		 posicionarCortina(dato); //Funcion que posiciona la cortina un porcentaje dado por el usuario y queda fija
		 flag_cortinaLibre=0;
		  automatico=0; 		//Desactiva Automatico ya que deja la cortina en una posicion fija
	 }
	if(flag_setearAutomatico)
	{
		  SetearAutomatico(dato); //Funcion que recibe dato recibido por bluetoth lo procesa y convierte y setea la hora de levantar y bajar la cortina
		  flag_setearAutomatico=0;
	}
	}
      }else{
	 
        if(++contadorCortinaOcupada==cortina_getCantidadBajar){ //Cuando la cortina esta girando solo verifica cuando debe parar ignorando las demas solicitudes
	    motor_parar();
	    flag_cortinaLibre=1;
	    contadorCortinaOcupada=0;
	 }
void SysTick_Handler()	//Interrupcion que ocurre cada 100 ms
{
	sEOS_SCH_Tareas();	//Ejecuta el planificador de tareas
}


static uint8_t detectarHoraAutomatico() //Devuelve true si debe funcionar el automatico
{	
   if (gethora_Act()>=gethora_Subir) && (getmin_Act>=getmin_subir) && (gethora_Act()<=gethora_Bajar) && (getmin_Act<=getmin_Bajar) 
      {
      return 1;	//Reorna true si esta dentro de los margenes de funcionar automatico
    else
     return 0;	//Retorna false si no esta dentro de los margenes
      }
  }
   
 
   }