/*
Proyecto: Robot móvil para desinfectar ambientes interiores con luces UV.
Libreria: Sistema de Percepción - Lectura ADC de los sensores. 
Archivo: ADCModule.h
Autores:Santiago Duque Ramos - 1733527 
        Juan José López Flórez - 1730514 
        Jorge Luis Leiton Arias - 1730004
*/

void configuracionADC();
void posicionADC(int posicion);
void inicioADC();
void limpiezaDebandera();
int lecturaADC();
int distancia(int lectura);