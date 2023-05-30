# SeminarioSistemasOperativos_Actividad-06
**Requerimientos:**<br>
1. En esta práctica se contempla el diagrama de Cinco Estados:
a. Nuevo: Procesos que se acaban de crear pero aún no han sido admitidos por el sistema
operativo en el grupo de procesos ejecutables.
b. Listos: Procesos que están preparados para ejecutarse, en cuanto sea su turno.
c. Ejecución: Proceso que está actualmente en ejecución.
d. Bloqueado: Proceso que no puede ejecutar hasta que se produzca cierto suceso, como
la terminación de una operación de E/S.
e. Terminado: Un proceso que ha sido excluido por el sistema operativo del grupo de
procesos activos, bien porque se detuvo o porque fue abandonado por alguna razón.
2. El algoritmo por implementar para la cola de listos es el FCFS es decir los procesos se
ordenarán conforme van llegando.
3. Se preguntará el Número de Procesos inicial pudiendo ser N procesos.
4. El máximo de procesos en memoria será de 4 (Recuerde que los estados a considerar en
este
caso son: Ejecución, Bloqueado y Listo).
5. Los procesos que no tengan cupo en la cola de listos deberán quedarse en la cola de
Nuevos,
esperando a que algún proceso termine y así ingresar al sistema.
6. A cada uno de los procesos que se generan (punto 3) se le asignará internamente:
a. Identificador de proceso único. (Puede ser secuencial)
b. Tiempo máximo estimado (aleatorio, validar que sea mayor a 0 y en un rango entre
5 y 16).
c. Datos para la operación a realizar (aleatorio, validar error aritmético). (Ver punto 2
de la actividad 4 (programa 2)).
7. Las teclas a utilizar son:
Tecla ¿Qué indica? ¿Qué hace?
I Interrupción
por entradasalida (pasa a
estado
bloqueado)
El proceso que está en uso del procesador (ejecución) debe salir
de este y esperar a que se lleve a cabo la solicitud realizada para
luego poder continuar con su ejecución (planificador a corto
plazo). Para este programa si se presiona “I” el proceso en
ejecución saldrá del procesador y se irá a la cola de Bloqueados,
permaneciendo allí un tiempo de 8, al terminar este tiempo el
proceso pasará a la cola de listos a esperar su turno a usar el
procesador
E Error El proceso que se esté ejecutando en ese momento terminara por
error, es decir saldrá del procesador y se mostrara en terminados,
para este caso como el proceso no termino normalmente se
desplegara error en lugar de un resultado. (Recuerde que al
terminar un proceso queda un espacio en memoria que puede ser

ocupado al admitir un proceso nuevo)
P Pausa Detiene la ejecución de su programa momentáneamente, la
simulación se reanuda cuando se presione la tecla “C”.
C Continuar Al presionar esta tecla se reanudará el programa pausado
previamente con “P”.
Centro Universitario de Ciencias Exactas e Ingenierías
M. en C. Violeta del Rocío Becerra Velázquez
8. Deberá mostrarse en pantalla:
a. Listar número de procesos en estado Nuevo. (Anteriormente se etiquetaba como
Número de Lotes Pendientes, recuerde que ahora ya no se manejan lotes así que se
listará el número de procesos en la cola de Nuevos).
b. Cola de listos:
i. Identificador de Proceso.
ii. Tiempo Máximo Estimado.
iii. Tiempo Transcurrido.
c. Proceso en Ejecución:
i. Se mostraran todos los datos correspondientes al proceso.
ii. Tiempo que ya ha sido ejecutado.
iii. Tiempo restante por ejecutar.
d. Cola de Bloqueados
i. Identificador de Proceso.
ii. Tiempo transcurrido en bloqueado.
e. Procesos Terminados
i. Identificador de Proceso.
ii. Operación.
iii. Resultado de la operación o bien ERROR cuando el proceso haya sido
terminado con la tecla “E”.
f. Reloj, es decir, el contador del tiempo total transcurrido desde el inicio de la
simulación hasta su término.
9. Se deberá calcular los siguientes tiempos;
a. Tiempo de Llegada: Hora en la que el proceso entra al sistema.
b. Tiempo de Finalización: Hora en la que el proceso termino.
c. Tiempo de Retorno: Tiempo total desde que el proceso llega hasta que termina.
d. Tiempo de Respuesta: Tiempo transcurrido desde que llega hasta que es atendido por
primera vez.
e. Tiempo de Espera: Tiempo que el proceso ha estado esperando para usar el
procesador.
f. Tiempo de Servicio: Tiempo que el proceso ha estado dentro del procesador. (Si el
proceso termino su ejecución normal es el TME, de no ser así es el tiempo
transcurrido)
10. El programa terminará cuando todos los procesos se hayan ejecutado.
11. Mostrar al finalizar todos los datos de cada proceso, incluyendo los tiempos marcados
en el
punto 9, además de número de programa y si termino por error o normal.

Para la entrega del programa deberá realizar un video con las especificaciones que se
soliciten al momento de la explicación, además deberá tener un reporte de este el cual
consta de:
• Datos personales
• Datos de la materia
• Número de actividad
• Objetivo de la actividad
• Notas acerca del lenguaje, como soluciono y conclusiones.
