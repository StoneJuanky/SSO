# SSO-Actividad-10
**Requerimientos:**<br>
1. Se cumplirán con todas las especificaciones de la práctica anterior, con excepción del algoritmo de planificación, se manejará la cola de listos utilizando el algoritmo de planificación Round-Robin.
2. Preguntar el Número de Procesos Inicial (n procesos).
3. Preguntar el valor del Quantum.
4. Recuerde que el algoritmo RR es con ráfagas de tiempo, el cual lo determina el valor del Quantum, es decir, cuando el valor correspondiente al Quantum haya transcurrido, el proceso saldrá del procesador para formarse al final de la cola de listos.
5. Teclas a utilizar:
Tecla ¿Qué indica? ¿Qué hace?
    -	E Interrupción por entrada-salida (pasa a estado bloqueado) El proceso que está en uso del procesador (ejecución) debe salir de este y esperar a que se lleve a cabo la solicitud realizada para luego poder continuar con su ejecución (planificador a corto plazo). Para este programa si se presiona “E” el proceso en ejecución saldrá del procesador y se irá a la cola de Bloqueados, permaneciendo allí un tiempo de 7, al terminar este tiempo el proceso pasará a la cola de listos a esperar su turno a usar el procesador.
    -	W Error El proceso que se esté ejecutando en ese momento terminara por error, es decir saldrá del procesador y se mostrara en terminados, para este caso como el proceso no termino normalmente se desplegara error en lugar de un resultado (Recuerde que al terminar un proceso queda un espacio en memoria que puede ser ocupado al admitir un proceso nuevo).
    -	P Pausa Detiene la ejecución de su programa momentáneamente, la simulación se reanuda cuando se presione la tecla “C”.
    -	C Continuar Al presionar esta tecla se reanudará el programa pausado previamente con “P”.
    - N Nuevo Al presionar esta tecla se generará un nuevo proceso, creando con ello los datos necesarios de forma aleatoria. El planificador a largo plazo es el que definirá su ingreso al sistema (recordar el máximo de procesos en memoria).
    - B Tabla de procesos (BCP de cada proceso) Al presionar esta tecla el programa se pausara y se deberá visualizar la tabla de procesos, es decir los BCP de cada uno de los procesos. Con la tecla “C” continua la simulación de su programa en el punto donde quedó.
6. Deberá mostrarse en pantalla:
- Listar número de procesos en estado Nuevo.
- Valor del Quantum.
- Cola de listos:
  - Identificador de Proceso.
  - Tiempo Máximo Estimado.
  - Tiempo Transcurrido.
  - Se debe notar el avance del carrusel.
- Proceso en Ejecución:
  - Se mostraran todos los datos correspondientes al proceso.
  - Tiempo transcurrido en ejecución.
  - Tiempo restante por ejecutar.
  - Tiempo transcurrido del quantum.
- Cola de Bloqueados
  - Identificador de Proceso.
  - Tiempo transcurrido en bloqueado.
- Procesos Terminados
  - Identificador de Proceso.
  - Operación.
  - Resultado de la operación o bien ERROR cuando el proceso haya sido terminado con la tecla “W”.
- Reloj, es decir, el contador del tiempo total transcurrido desde el inicio de la simulación hasta su término.
7. El programa terminará cuando todos los procesos se hayan ejecutado (pausar la pantalla al terminar para observar).
8. Mostrar al finalizar todos los datos de cada proceso, es decir, la tabla de procesos.
Para la entrega del programa deberá realizar un video con las especificaciones que se soliciten al momento de la explicación, además deberá tener un reporte de este el cual consta de:<br>
• Datos personales<br>
• Datos de la materia<br>
• Número de actividad<br>
• Objetivo de la actividad<br>
• Notas acerca del lenguaje, como soluciono y conclusiones. <br><br>
**Entregables:**<br>
Código fuente (si el lenguaje en el que trabaja lo permite entregue el ejecutable), reporte y video de no más de 5 minutos. Para el video puede dejar la liga en el mismo reporte y subir el video a drive o YouTube. Deberá subir un solo archivo (si es necesario en comprimido) a la plataforma de moodle2, en tiempo y forma. El nombre del archivo deberá estar compuesto por su primer apellido, su primer nombre, sección y número de actividad, por ejemplo: BecerraVioletaD01Act6.pdf. Si se pasa de la fecha de entrega tendrá oportunidad de entrega tardía en Classroom con un menor puntaje.
