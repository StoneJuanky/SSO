# SSO-Actividad-14
**Requerimientos:**<br>
1. El algoritmo de planificación a implementar es el de RR (Actividad 10).
2. Cumplir con todos los requerimientos del programa 5 (actividad 10).
3. De manera aleatoria se asignará, el tiempo, operación y tamaño de cada proceso (número aleatorio entero entre 6 y 25).
4. El tamaño de la memoria será de 200.
5. Dividir la memoria en “Marcos” de Igual longitud (40 marcos de 5 cada uno).
6. El S.O. ocupará 2 marcos, quedando 38 disponibles para repartir entre los procesos.
7. Dividir los procesos en páginas (tamaño 5), es decir dividir los procesos de igual tamaño que los marcos (5).
8. Teclas a utilizar:
Tecla ¿Qué indica? ¿Qué hace?
    -	E Interrupción por entrada-salida (pasa a estado bloqueado) El proceso que está en uso del procesador (ejecución) debe salir de este y esperar a que se lleve a cabo la solicitud realizada para luego poder continuar con su ejecución (planificador a corto plazo). Para este programa si se presiona “E” el proceso en ejecución saldrá del procesador y se irá a la cola de Bloqueados, permaneciendo allí un tiempo de 7, al terminar este tiempo el proceso pasará a la cola de listos a esperar su turno a usar el procesador.
    -	W Error El proceso que se esté ejecutando en ese momento terminara por error, es decir saldrá del procesador y se mostrara en terminados, para este caso como el proceso no termino normalmente se desplegara error en lugar de un resultado (Recuerde que al terminar un proceso queda un espacio en memoria que puede ser ocupado al admitir un proceso nuevo).
    -	P Pausa Detiene la ejecución de su programa momentáneamente, la simulación se reanuda cuando se presione la tecla “C”.
    -	C Continuar Al presionar esta tecla se reanudará el programa pausado previamente con “P”.
    - N Nuevo Al presionar esta tecla se generará un nuevo proceso, creando con ello los datos necesarios de forma aleatoria. El planificador a largo plazo es el que definirá su ingreso al sistema (recordar el máximo de procesos en memoria).
    - B Tabla de procesos (BCP de cada proceso) Al presionar esta tecla el programa se pausara y se deberá visualizar la tabla de procesos, es decir los BCP de cada uno de los procesos. Con la tecla “C” continua la simulación de su programa en el punto donde quedó.
    - T Tabla de Páginas Al presionar esta tecla se detendrá la ejecución y se mostrara la tabla de páginas de cada proceso, además de los marcos libres. Continuará al presionar la tecla “C
9. Para que el proceso pueda estar en la cola de listos (en memoria), deberá existir espacio en memoria, es decir, deben de existir los marcos libres necesarios para albergar el proceso.
10. Deberá mostrarse en pantalla:
- La memoria dividida en “Marcos”, no olvidando contemplar el espacio que ocupa el S. O., (se debe señalar el número de cada marco), mostrando en todo momento si están ocupados o no, marcándolos en proporción. (Ver figura)
- El número de procesos que están en la cola de nuevos
  - Del proceso que esta por ingresar a Listos, deberá mostrarse su ID y su tamaño, para así visualizar cuantos marcos libres se necesitarán.
- El proceso en ejecución mostrando todos sus datos.
- El contador que representa el Quantum.
- Listar los terminados, marcando los que tuvieron error
- El contador global.
11. En la tabla de páginas, deberá observarse que página está en que marco, (es una entrada por proceso). Además deberá mostrarse la relación de marcos libres.
12. El programa terminará cuando todos los procesos se hayan ejecutado (pausar la pantalla al terminar para observar).
<table class="tftable" border="1">
<tr><th>No. Marco</th><th>No. Marco</th></tr>
<tr><td>0</td><td>1</td></tr>
<tr><td>2</td><td>3</td></tr>
<tr><td>4</td><td>5</td></tr>
<tr><td>6</td><td>7</td></tr>
<tr><td>8</td><td>9</td></tr>
<tr><td>10</td><td>11</td></tr>
<tr><td>12</td><td>13</td></tr>
<tr><td>14</td><td>15</td></tr>
<tr><td>16</td><td>17</td></tr>
<tr><td>18</td><td>19</td></tr>
<tr><td>20</td><td>21</td></tr>
<tr><td>22</td><td>23</td></tr>
<tr><td>24</td><td>25</td></tr>
<tr><td>26</td><td>27</td></tr>
<tr><td>28</td><td>39</td></tr>
<tr><td>30</td><td>31</td></tr>
<tr><td>32</td><td>33</td></tr>
<tr><td>34</td><td>35</td></tr>
<tr><td>36</td><td>37</td></tr>
<tr><td>38</td><td>39</td></tr>
</table>
Para la entrega del programa deberá realizar un video con las especificaciones que se soliciten al momento de la explicación, además deberá tener un reporte de este el cual consta de:<br>
• Datos personales<br>
• Datos de la materia<br>
• Número de actividad<br>
• Objetivo de la actividad<br>
• Notas acerca del lenguaje, como soluciono y conclusiones. <br><br>
**Entregables:**<br>
Código fuente (si el lenguaje en el que trabaja lo permite entregue el ejecutable), reporte y video de no más de 5 minutos. Para el video puede dejar la liga en el mismo reporte y subir el video a drive o YouTube. Deberá subir un solo archivo (si es necesario en comprimido) a la plataforma de moodle2, en tiempo y forma. El nombre del archivo deberá estar compuesto por su primer apellido, su primer nombre, sección y número de actividad, por ejemplo: BecerraVioletaD01Act6.pdf. Si se pasa de la fecha de entrega tendrá oportunidad de entrega tardía en Classroom con un menor puntaje.
