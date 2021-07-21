/*
Proyecto: Robot móvil para desinfectar ambientes interiores con luces UV.
Libreria: Sistema de control - Logica de control. 
Archivo: fuzzy.c
Autores: Santiago Duque Ramos - 1733527, 
        Juan José López Flórez - 1730514, 
        Jorge Luis Leiton Arias - 1730004
*/

#include<math.h>
#include <avr/io.h>

/* Funcion de membresia triangular donde a y c es la base, b el centro y x la entrada */
float Mtriangular(float x,float a, float b,float c){
    float salida = 0;
    //No esta en el triangulo
    if( (x <= a) || (x >= c) ){
        return salida;  
    }
    //Recta con pendiente positiva
    if( (a < x) && (x <= b) ){
        salida = (x-a)/(b-a);  
        return salida;
    }
    //Recta con pendiente negativa
    if( (b < x) && (x < c) ){
        salida = (c-x)/(c-b);
        return salida;
    }
    return salida;
}

/* Funcion de membresia trapesoidal donde a y d es la base, b y c el centro y x la entrada. 
Para la forma abierta repetir los ultimos parametros o los primeros ej(1,1,2,3), es abierta por la izquierda. */
float Mtrapezoidal(float x,float a,float b,float c,float d){
    float salida = 0;
    //Si es abierta por la izquierda
    if (a == b){
        if( (x <= a) || (x <= c) ){
            salida = 1;
            return salida;
        }
        if( (c < x) && (x < d) ){
            salida = (d-x)/(d-c);
            return salida;
        }
        if( (x >= d) ){
            salida = 0;
            return salida;
        }
    }
    //Si es abierta por la derecha
    if(c == d){
        if( (x >= d) || (x >= b) ){
            salida = 1;
            return salida;
        }
   
        if( (a < x) && (x < b) ){
            salida = (x-a)/(b-a);
            return salida;
        }
        if( (x <= a) ){
            salida = 0;
            return salida;
        }
        return salida;
    }
    //No esta en el trapecio
    if( (x <= a) || (x >= d) ){
        return salida;
    }
    //Recta con pendiente positiva
    if( (a < x) && (x < b) ){
        salida = (x-a)/(b-a);
        return salida;
    }
    //constante 1
    if( (b < x) && (x < c) ){
        salida = 1;
        return salida;
    }
    //Recta con pendiente negativa
    if( (c < x) && (x < d) ){
        salida = (d-x)/(d-c);
        return salida;
    }
    return salida;
}

/*Funcion para evaluar la entrada en la salida, corta, une y difuzzifica dando una salida al actuador. */
int VariablesLinguistcasSalida(float Lizqierda,float Lcentro,float LDerecha,int u){
	//Universo de discurso para la salida es [0,100]
	//Lizqierda es el limite de valor que puede alcanzar el trapecio izquierdo
	//Lcnetro es el limite de valor que puede alcanzar el triangulo 
	//LDerecha es el limite de valor que puede alcanzar el trapecio derecho
	int x = 0;
	float centroideNumerador = 0;
	float centroideDenominador = 0;
	//int resultado = 0;
	//float salidaTIZ = 0;
	//float salidaTCE = 0;
	float salidaTCD = 0;
	float salida=0;
	int j = 0; //Indicador en que posicion esta.
	for(x=0;x<u;x++){ //Universo de discurso
		//Reinicio de variables
		float salidaTIZ = 0;
		float salidaTCE = 0;
		salidaTCD = 0;
		j = 0;
		//Trapecio abierto del lado izquierdo
        if( (x <= 10) ){
            salidaTIZ = Lizqierda;
            j = 1;
        }
        if( (10 < x) && (x < 30) ){
        	salidaTIZ = (30-x);
        	salidaTIZ = salidaTIZ/20;
        	j = 1;
			if(salidaTIZ > Lizqierda){
				salidaTIZ = Lizqierda;
			}
        }
        //triangulo
        //Recta con pendiente positiva
    	if( (10 <= x) && (x <= 30) ){
			j = 1;
	        salidaTCE = (x-10);
	        salidaTCE = salidaTCE/20;
	        if(salidaTCE > Lcentro){
				salidaTCE = Lcentro;
			}
    	}
    	//Recta con pendiente negativa
	    if( (30 < x) && (x < 50) ){
	        salidaTCE = (50-x);
	        salidaTCE = salidaTCE/20;
	        if(salidaTCE > Lcentro){
				salidaTCE = Lcentro;
			}
   		}
        //Trapecio abierto del lado derecho
     	if( (x >= 50) ){
            salidaTCD = LDerecha;
            if(salidaTCD > LDerecha){
			    salidaTCD = LDerecha;
			}  
        }
        if( (30 < x) && (x < 50) ){
		  	salidaTCD = (x-30);
		  	salidaTCD = salidaTCD/20;
		  	if(salidaTCD > LDerecha){
				salidaTCD = LDerecha;
			}
        }
        //Se hace la union de los conjuntos difusos, que seria el valor mas alto de cada ciclo
		if( (salidaTIZ >= salidaTCE) && (j == 1)){
		   	centroideNumerador +=  x*salidaTIZ;
		   	centroideDenominador += salidaTIZ;
		}
        else if((salidaTIZ < salidaTCE) && (j == 1)){
		   	centroideNumerador +=  x*salidaTCE;
		   	centroideDenominador += salidaTCE;
		} 
		if( (LDerecha >= salidaTCE) && (j == 0)){
		   	centroideNumerador +=  x*LDerecha;
		   	centroideDenominador += LDerecha;
		}
        else if((salidaTIZ < salidaTCE) && (j == 0)){
		   	centroideNumerador +=  x*salidaTCE;
		   	centroideDenominador += salidaTCE; 		
		}
	}
	salida =(centroideNumerador/centroideDenominador);
	return (int)salida;
}


