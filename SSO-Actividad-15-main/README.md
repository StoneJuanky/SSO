# SSO-Actividad-15
**Requerimientos:**<br>
1. El algoritmo de planificación a implementar es el de RR (Actividad 10).
2. Cumplir con todos los requerimientos del programa 5 (actividad 10).
3. De manera aleatoria se asignará, el tiempo, operación y tamaño de cada proceso
(número
aleatorio entero entre 6 y 25).
4. El tamaño de la memoria será de 200.
5. Dividir la memoria en “Marcos” de Igual longitud (40 marcos de 5 cada uno).
6. El S.O. ocupará 2 marcos, quedando 38 disponibles para repartir entre los procesos.
7. Dividir los procesos en páginas (tamaño 5), es decir dividir los procesos de igual tamaño
que
los marcos (5).
8. Teclas a utilizar:
Tecla ¿Qué indica? ¿Qué hace?
I Interrupción

por entrada-
salida (pasa a

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
A Tabla de
Páginas
Al presionar esta tecla se detendrá la ejecución y se mostrará la
tabla de páginas de cada proceso, además de los marcos libres.
Continuará al presionar la tecla “C”
9. Para que el proceso pueda estar en la cola de listos (en memoria), deberá existir espacio
en
memoria, es decir, deben de existir los marcos libres necesarios para albergar el proceso.
10. Deberá mostrarse en pantalla:
a. La memoria dividida en “Marcos”, no olvidando contemplar el espacio que ocupa el
S. O., (se debe señalar el número de cada marco), mostrando en todo momento si
están ocupados o no, marcándolos en proporción. (Ver figura)
b. El número de procesos que están en la cola de nuevos
i. Del proceso que esta por ingresar a Listos, deberá mostrarse su ID y su
tamaño, para así visualizar cuantos marcos libres se necesitarán.
c. El proceso en ejecución mostrando todos sus datos.
d. El contador que representa el Quantum.
e. Listar los terminados, marcando los que tuvieron error
f. El contador global.
11. En la tabla de páginas, deberá observarse que página está en que marco, (es una
entrada por
proceso). Además, deberá mostrarse la relación de marcos libres.
12. El programa terminará cuando todos los procesos se hayan ejecutado (pausar la
pantalla al
terminar para observar).
