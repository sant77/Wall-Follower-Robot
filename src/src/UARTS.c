/*
Proyecto: Robot móvil para desinfectar ambientes interiores con luces UV.
Libreria: Sistema de Comunicación - UART 
Archivo: UARTS.c 
Autor: Carlos Ql - https://www.youtube.com/watch?v=6uZd8qi66WA
Modificado: Santiago Duque Ramos - 1733527 
        	Juan José López Flórez - 1730514 
        	Jorge Luis Leiton Arias - 1730004
*/

#include <avr/io.h>

/* Funcion para inicializar los registros para trabajar con el modulo USART */
void UART_init()
{
	DDRD |= (1<<1);	//PD1 como salida TXa
	DDRD &= ~(1<<0); //PD0 como entrada RX
	UCSR0A = (0<<TXC0)|(0<<U2X0)|(0<<MPCM0);
	UCSR0B = (1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02)|(0<<TXB80);
    //Modo asincrono
    //Bit de parida desactivado
    //Bit de parada 1
    //Tamaño de los caracteres: 8bits
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0);
	UBRR0 = 103; //No duplica velocidad 9600B A 160000
}

/* Funcion para leer */
unsigned char UART_read(){
	if(UCSR0A&(1<<RXC0)){ //Si el bit7 del registro UCSR0A se ha puesto a 1
		return UDR0; //Devuelve el dato almacenado en el registro UDR0
	}
	else
	return 0;
}

/* Funcion para escribir un caracter */
void UART_write(unsigned char caracter){
	while(!(UCSR0A&(1<<5))); // Mientras el registro UDR0 esté lleno espera
	UDR0 = caracter; //Cuando el el registro UDR0 está vacio se envia el caracter
}

/* Funcion para escribir texto */
void UART_write_txt(char* cadena){ //Cadena de caracteres de tipo char
	while(*cadena !=0x00){ //Mientras el último valor de la cadena sea diferente a el caracter nulo
		UART_write(*cadena); //Transmite los caracteres de cadena
		cadena++; //Incrementa la ubicación de los caracteres en cadena
		//Para enviar el siguiente caracter de cadena
	}
}

