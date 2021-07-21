/*
Proyecto: Robot móvil para desinfectar ambientes interiores con luces UV.
Libreria: Sistema de Movimiento - Control de velocidad para los motores DC con PWM. 
Archivo: ControlPWM.c
Autores: Santiago Duque Ramos - 1733527, 
        Juan José López Flórez - 1730514, 
        Jorge Luis Leiton Arias - 1730004
*/
#include <avr/io.h>
#include <util/delay.h>

/* Funcion para colocar los pines D5 y D6 como PWM, y control de direccion de motor */
void configuracionPWM(){
  //Modo no inversor
  TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00) | (1 << COM0B1);;
  //Pre escaler de 8
  TCCR0B |= (1 <<CS01);  
  //Cilco de trabajo por defecto
  OCR0A = 0;
  OCR0B = 0;
  //Salidas PWM
  DDRD |= (1 << PD5);
  DDRD |= (1 << PD6);
  //Salida de control de direccion
  DDRB |= (1 << PB0)  | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4);
}

/* Funcion para el ciclo de trabajo del OCR0A */
void cicloDeTrabajoA(int valor){
    OCR0A = (valor*255)/(100);
}

/* Funcion para el ciclo de trabajo del puerto OCR0B */
void cicloDeTrabajoB(int valor){
    OCR0B = (valor*255)/(100);
}

/* Funcion para mover el motor A hacia adelante */
void motorA_avance(){
    PORTB  |=  (1 << PB0);
    PORTB  &= ~(0 << PB1);
}

/* Funcion para mover el motor A hacia atras */
void motorA_retroceso(){
     PORTB  |=  (1 << PB1);
     PORTB  &= ~(0 << PB0);
}

/* Funcion para mover el motor B hacia adelante */
void motorB_avance(){
    PORTB  |=  (1 << PB2);
    PORTB  &= ~(0 << PB3);
}

/* Funcion para mover el motor B hacia atras */
void motorB_retroceso(){
     PORTB  |=  (1 << PB3);
     PORTB  &= ~(0 << PB2);
}

/* Funcion para activar los LEDs UV */
void LEDON(){
     PORTB  |=  (1 << PB4);
}

/* Funcion para desactivar los LEDs UV */
void LEDOFF(){
     PORTB  &= ~(1 << PB4);
}

