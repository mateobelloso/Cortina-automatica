

static uint8_t cantidadBajar;



void posicionarCortina(uint8_t dato)
{
	    if(dato<porcetajeCortinaCerrada){
	     {
		  cantidadBajar=porcentajeCortinaCerrada-dato;
		motor_girar_derecha();      //Abrir la cortina (dato-porcentaje), x cantidad de porcentaje que equivale a x segundos para la derecha   
	    }
	    else
	    {
	       cantidadBajar=dato-porcentajeCortinaCerrada
	       motor_girar_izquierda();	//Cerra la cortina (dato-porcentaje), x cantidad de porcentaje que equivale a girar x segundos para la izquierda
	     }
	  }
	  
uint8_t cortina_getcantidadBajar(){
	     
   return cantidadBajar;
	  }	
	       
	 
   
	 
	 
	 
 
	 
//100 %Full Cerrada
//0% %nada cerrada    
 