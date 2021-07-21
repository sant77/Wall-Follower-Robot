/*
Proyecto: Robot móvil para desinfectar ambientes interiores con luces UV.
Archivo: main.c 
Autores: Santiago Duque Ramos - 1733527 
        	Juan José López Flórez - 1730514 
        	Jorge Luis Leiton Arias - 1730004
*/

/* Inclusion de las librerias */
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ControlPWM.h"
#include "ADCModule.h"
#include "fuzzy.h"
#include "UARTS.h"

/* Definicion de variables para la medicion y calculo de la distancia */
volatile  int i=1;
int lectura=0;
int distancia0=0;
int distancia0P=0;
int distancia1P=0;
int distancia1=0;
int distancia2P=0;
int distancia2=0;
int promedio=0;
int promedio1=0;
int promedio2=0; 

/*Funcion para intercambiar */
void swap ( int *x, int *y ) {
  int tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

/* Funcion principal */
int main(void){
    //Configuracion del ADC y UART
    configuracionADC();
    posicionADC(0);
    inicioADC();
    UART_init();
    //Configuracion de PWM y motores
    configuracionPWM();
    cicloDeTrabajoA(0);
    cicloDeTrabajoB(0); //Motor con velocidad constante
    motorA_avance();
    motorB_avance();
  
    //Variables para uso interno de control 
    int error = 0;
    int referencia = 10;
    float error_negativo = 0.0;
    float error_central = 0.0;
    float error_positivo = 0.0;
    int ajuste_de_distancia = 0 ;

    uint8_t dato=0;
    int salida = 0;
    while(salida == 0){
        dato = UART_read();
		if(dato != 0){
			switch(dato){
				case 'C':
					referencia = 5;
					
				break;
                case 'D':
					referencia = 10;
					
				break;
                case 'E':
					referencia = 15;
					
				break;
				case 'N':
					//UART_write_txt("Esto hace algo\n\r");
                    //Esto asignaria la velocidad pero por problemas con los sensores no se va a asignar
				break;
                case 'A':
                    //Activacion de los LED UV
                    LEDON();
                    salida = 1;
				break;
			}
        }
    }
    cicloDeTrabajoA(30); //Motor con velocidad constante
    cicloDeTrabajoB(30); //Motor con velocidad constante
    salida = 0;
    sei(); //Interrupcion global
	while(salida == 0){
        dato = UART_read();
        error = referencia - promedio ;//referencia - la distancia actual
        if (promedio2 <= 12){
            /*distancia_choque_cercana =  Mtrapezoidal(promedio2,0, 0, 10, 20);
            distancia_choque_normal  =  Mtriangular(promedio2,15, 20, 25);
            ajuste_de_esquive = VariablesLinguistcasSalida(0.0,distancia_choque_normal,distancia_choque_cercana, 81);
            */
            cicloDeTrabajoA(20);
            cicloDeTrabajoB(0);
        }
        else if(promedio1 <= 12){
            /*distancia_choque_cercana =  Mtrapezoidal(distancia1,0, 0, 10, 20);
            distancia_choque_normal  =  Mtriangular(distancia1,15, 20, 25);
            ajuste_de_esquive = VariablesLinguistcasSalida(0.0,distancia_choque_normal,distancia_choque_cercana, 81);
            */
            cicloDeTrabajoA(20);
            cicloDeTrabajoB(0);
        }
        else if(error <= -10){
            cicloDeTrabajoA(22);
            cicloDeTrabajoB(30);
        }
        else if(error >= 6){
            cicloDeTrabajoA(41);
            cicloDeTrabajoB(30);
        }
        else{
            cicloDeTrabajoB(30);
            error_negativo =  Mtrapezoidal(error,-30, -30, -10, 0);
            error_central  =  Mtriangular(error,-30, 0, 30);
            error_positivo =  Mtrapezoidal(error,0, 10, 30, 30);  
            ajuste_de_distancia = VariablesLinguistcasSalida(error_negativo,error_central,error_positivo, 81);
            cicloDeTrabajoA(ajuste_de_distancia);

        /*
        UART_write_txt("PWM: ");
        itoa(ajuste_de_distancia, bus2, 10);
        UART_write_txt(bus2);
        UART_write_txt("\n\r");
        UART_write_txt("Sensor: ");
        itoa(promedio, bus2, 10);
        UART_write_txt(bus2);
        UART_write_txt("\n\r");
        */
        }
        if(dato != 0){
            switch(dato){
				case 'B':
					cicloDeTrabajoA(0);
                    LEDOFF();
                    cicloDeTrabajoB(0);
                    salida = 1;	
				break;
			}
        }
    }
}

ISR(ADC_vect){
    lectura = lecturaADC();
    if(i==1){
        distancia2 = distancia(lectura);
        swap(&distancia2,&distancia2P);
        promedio2 = (distancia2 + distancia2P) / 2; 
        posicionADC(0);
        if(promedio2 == 0 || promedio2 == 1 || promedio2 == 2 || promedio2 == 3 ){
            promedio2 = 25 ;
        }  
    }
    if(i==2){
        distancia0 = distancia(lectura);
        swap(&distancia0,&distancia0P);
        promedio = (distancia0 + distancia0P) / 2; 
        posicionADC(1);
    }

    if(i==3){
        distancia1 = distancia(lectura);
        swap(&distancia1,&distancia1P);
        promedio1 = (distancia1 + distancia1P) / 2; 
        posicionADC(2);
         if(promedio1 == 0 || promedio1 == 1 || promedio1 == 2 || promedio1 == 3 ){
            promedio1 = 25 ;
        }
        i = 0;
    }
    i++;
    inicioADC();
}

