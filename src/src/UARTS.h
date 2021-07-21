/*
Proyecto: Robot móvil para desinfectar ambientes interiores con luces UV.
Libreria: Sistema de Comunicación - UART 
Archivo: UARTS.h 
Autor: Carlos Ql - https://www.youtube.com/watch?v=6uZd8qi66WA
Modificado: Santiago Duque Ramos - 1733527 
        	Juan José López Flórez - 1730514 
        	Jorge Luis Leiton Arias - 1730004
*/

void UART_init();						
unsigned char UART_read();				
void UART_write(unsigned char);				
void UART_msg(char*);						
void UART_write_txt(char* cadena);
