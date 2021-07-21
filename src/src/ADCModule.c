/*
Proyecto: Robot móvil para desinfectar ambientes interiores con luces UV.
Libreria: Sistema de Percepción - Lectura ADC de los sensores. 
Archivo: ADCModule.c
Autores:Santiago Duque Ramos - 1733527 
        Juan José López Flórez - 1730514 
        Jorge Luis Leiton Arias - 1730004
*/
#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>

/* Funcion para configurar el ADC */
void configuracionADC(){
    //ADC como una entrada
    //Referencia de voltaje externo 
    ADMUX |= (1<< REFS0) ;  
    //PreEscaler a 128 
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    //Interrupcion ADC activada
    ADCSRA |=  (1 << ADIE);
}

/* Funcion para asignar cual ADC realizara la conversion */
void posicionADC(int posicion){
    //Reinicio de los registros
    ADMUX &= ~(1 << MUX0);
    ADMUX &= ~(1 << MUX1);
    ADMUX &= ~(1 << MUX2);
    ADMUX &= ~(1 << MUX3);
    //Seleccion de estados
    if (posicion == 8)
    {
        ADMUX |= (1 << MUX3);
    }else if (posicion == 7)
    {
        ADMUX |= (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
    }else if (posicion == 6)
    {
        ADMUX |= (1 << MUX2) | (1 << MUX1);
    }else if (posicion == 5)
    {
        ADMUX |= (1 << MUX2)| (MUX0);
    }else if (posicion == 4)
    {
        ADMUX |= (1 << MUX2);
    }else if (posicion == 3)
    {
        ADMUX |= (1 << MUX1) | (1 << MUX0);
    }else if (posicion == 2)
    {
        ADMUX |= (1 << MUX1);
    }else if (posicion == 1)
    {
        ADMUX |= (1 << MUX0);
    }else
    {
        //Canal 0
    }
}

/* Funcion para iniciar la convercion del ADC */
void inicioADC(){
    ADCSRA |= (1 << ADEN) | (1 << ADSC);
}

/* Funcion para limpiar el bit ADIF */
void limpiezaDebandera(){
    ADCSRA  |= (1 << ADIF);
}

/* Funcion para dar el valor leido del ADC */
int lecturaADC(){
	int Ain,AinLow;
	AinLow = (int)ADCL;		//Lee los bits menos significativos
	Ain = (int)ADCH*256;	//Lee los mas significativos y multiplica por su peso
	Ain = Ain + AinLow;		//Suma las parte alta con la baja
	return(Ain);			//Retorna el resultado
}

/* Funcion para convertir el valor de la lectura del ADC en cm */
int distancia(int lectura){
    int distancia;
    //Conversion de ADC a cm
    distancia = 13*pow(lectura*0.0048828125,-1);
    //Correcion ante desviacion 
    if( (distancia >= 17) && (distancia <= 23) ){
        distancia = distancia + 1;
    }
    if( (distancia >= 24) && (distancia <= 30) ){
        distancia = distancia + 2;
    }
    return distancia;
}