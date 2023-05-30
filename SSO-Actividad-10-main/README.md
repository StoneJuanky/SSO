# SSO-Actividad-10
**Requerimientos:**<br>
1. Se cumplirán con todas las especificaciones de la práctica anterior, con excepción del
algoritmo de planificación, se manejará la cola de listos utilizando el algoritmo de
planificación Round-Robin.
2. Preguntar el Número de Procesos Inicial (n procesos).
3. Preguntar el valor del Quantum.
4. Recuerde que el algoritmo RR es con ráfagas de tiempo, el cual lo determina el valor del
Quantum, es decir, cuando el valor correspondiente al Quantum haya transcurrido, el
proceso
saldrá del procesador para formarse al final de la cola de listos.
5. Teclas para utilizar:
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
N Nuevo Al presionar esta tecla se generará un nuevo proceso, creando con
ello los datos necesarios de forma aleatoria. El planificador a
largo plazo es el que definirá su ingreso al sistema (recordar el
máximo de procesos en memoria)
T Tabla de
procesos
(BCP de cada
proceso)
Al presionar esta tecla el programa se pausará y se deberá
visualizar la tabla de procesos, es decir los BCP de cada uno de

los procesos. Con la tecla “C” continua la simulación de su
programa en el punto donde quedó.
6. Deberá mostrarse en pantalla:
a. Listar número de procesos en estado Nuevo.
b. Valor del Quantum.
c. Cola de listos:
i. Identificador de Proceso.
ii. Tiempo Máximo Estimado.
Centro Universitario de Ciencias Exactas e Ingenierías
M. en C. Violeta del Rocío Becerra Velázquez
iii. Tiempo Transcurrido.
iv. Se debe notar el avance del carrusel.
d. Proceso en Ejecución:
i. Se mostrarán todos los datos correspondientes al proceso.
ii. Tiempo transcurrido en ejecución.
iii. Tiempo restante por ejecutar.
iv. Tiempo transcurrido del quantum.
e. Cola de Bloqueados
i. Identificador de Proceso.
ii. Tiempo transcurrido en bloqueado.
f. Procesos Terminados
i. Identificador de Proceso.
ii. Operación.
iii. Resultado de la operación o bien ERROR cuando el proceso haya sido
terminado con la tecla “E”.
g. Reloj, es decir, el contador del tiempo total transcurrido desde el inicio de la
simulación hasta su término.
7. El programa terminará cuando todos los procesos se hayan ejecutado (pausar la
pantalla al
terminar para observar).
8. Mostrar al finalizar todos los datos de cada proceso, es decir, la tabla de procesos.
Para la entrega del programa deberá realizar un video con las especificaciones que se
soliciten al momento de la explicación, además deberá tener un reporte de este el cual
consta de:
• Datos personales
• Datos de la materia
• Número de actividad
• Objetivo de la actividad
• Notas acerca del lenguaje, como soluciono y conclusiones.
