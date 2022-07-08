
# Wall-Follower-Robot
En este proyecto se diseñó un Robot que fuera capaz de seguir una pared y esquivar obstáculos. Además, el robot se configuró para ser controlado por una aplicación móvil, donde el usuario, encendía o apagaba el robot y definía una distancia de seguimiento.
Los materiales usados para el diseño y creación del proyecto se encuentran en la documentación. Hay que agregar que el robot tenía pensado llevar un sistema de luces UV para desinfectar el ambiente. Sin embargo, estas terminaron siendo decorativas debido a que se usaron luces UVA y para la desinfección se suele usar UVC. Dado que el proyecto se realizó en pandemia, era difícil conseguir luces con una menor longitud de onda. Además, se utilizaron luces UVA para evitar posibles daños como quemaduras en la piel.

## Esquemático
<img align='center' src="docs/esquematico.png" width="500">

## PCB
<img align='center' src="docs/placa.png" width="500">

## Aplicación
Se diseñó una aplicación para hacer la comunicación con el robot, por medio de la programación del modulo USART. El apk de la aplicación se encuentra en la documentación y fue creado con la plataforma AppInventor.

## Conclusión y mejoras a futuro
El robot tuvo éxito en lograr seguir una pared, pero bajo desempeño esquivando obstáculos. Además, en el seguimiento de pared, a veces el sistema de control no era capaz de correguir el rumbo del robot cuando tomaba ángulos muy pronunciados con respecto a la pared. Esto se debe, principalmente a la disposición de los sensores. 
Para mejoras a futuro se puede probar colocando dos sensores en los laterales, mejorando así, la zona de sensado. También, es posible que los sensores ultra sonicos tengan mejores resultados que los sensores Chart.

## Links
 - Link para descargar el esquemático y PCB https://oshwlab.com/Santiago77/robot-seguir-de-pared
 - Link del video donde se basó el diseño del controlador Fuzzy https://www.youtube.com/watch?v=KDdm_DOEzpI

## Agradecimientos
Este proyecto no fue hecho por solo una persona, agradecimientos a Juan José López por el apoyo en la programación de los modulos y diseño de la aplicación. También a Jorge Luis Leiton por la ayuda en el diseño esquemático y PCB.
