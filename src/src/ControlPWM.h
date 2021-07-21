/*
Proyecto: Robot móvil para desinfectar ambientes interiores con luces UV.
Libreria: Sistema de Movimiento - Control de velocidad para los motores DC con PWM. 
Archivo: ControlPWM.h
Autores: Santiago Duque Ramos - 1733527, 
        Juan José López Flórez - 1730514, 
        Jorge Luis Leiton Arias - 1730004
*/

void configuracionPWM();
void cicloDeTrabajoA(int valor);
void cicloDeTrabajoB(int valor);
void motorA_avance();
void motorA_retroceso();
void motorB_avance();
void motorB_retroceso();
void LEDON();
void LEDOFF();