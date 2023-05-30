# SeminarioSistemasOperativos_Actividad-04
**Requerimientos:**<br>
1. El programa preguntará el número de trabajos inicial, para luego conformar lotes con capacidad máxima de 4 (ver Requerimientos programa 1).
2. En esta simulación la información de cada trabajo se generará internamente, es decir ya no será necesario introducir datos desde teclado, la información a generar es:
a. Número de cada proceso, validar que sea único. (Puede ser consecutivo)
b. Tiempo Máximo Estimado, se generará de forma aleatoria, validando que sea mayor a 0 (rango entre 6 y 15).
c. Operación (+, -, *, /, residuo, potencia) a realizar con sus operandos (validar operaciones), aleatoriamente.
3. Los trabajos se ejecutarán conforme a su número asignado (ID).
4. Los procesos una vez en ejecución pueden ser Interrumpidos por Entrada/Salida o bien terminados por Error (Observar la diferencia en la tabla).
5. La interrupción y la terminación de los trabajos en ejecución, se generaran por medio de teclas.
6. Las teclas a utilizar son:
   - E Interrupción por entrada-salida El proceso que está en uso del procesador (ejecución) debe salir de este e ir a la cola de los procesos del lote en ejecución (actual).
   - W Error El proceso que se esté ejecutando en ese momento terminara por error, es decir saldrá del procesador y se mostrara en terminados, para este caso como el proceso no termino normalmente se desplegara error en lugar de un resultado.
   - P Pausa Detiene la ejecución de su programa momentáneamente, la simulación se reanuda cuando se presione la tecla “C”.
   - C Continuar Al presionar esta tecla se reanudará el programa pausado previamente con “P”.
7. Deberá mostrarse en pantalla:
    - Procesos en Espera correspondientes al Lote en ejecución:
      - Número de Programa (en el programa anterior se listaba nombre del programador ahora es número de programa).
      - Tiempo Máximo Estimado.
      - Mostrar el tiempo transcurrido. En el caso de que el proceso no se haya ejecutado aún se desplegara 0.
    - Número de Lotes Pendientes: Especificar el número de lotes pendientes por ejecutar, si no hay se mostrará 0.
    - Proceso en Ejecución:
      - Se mostraran todos los datos correspondientes al proceso.
      - Tiempo que ya ha sido ejecutado.
      - Tiempo restante por ejecutar
    - Trabajos Terminados:
      - Número de Programa.
      - Operación
      - Resultado de la operación o bien ERROR cuando el proceso haya sido terminado con la tecla que genera error.
    - Reloj (Contador General).
8. Al terminar el lote en ejecución, continuará con el siguiente lote en espera.
9. El programa terminará cuando todas las operaciones de todos los lotes se hayan realizado (Pausarlo).

**Entregables:**<br>
         Código fuente (si el lenguaje en el que trabaja lo permite entregue el ejecutable), reporte y vídeo de no más de 5 minutos. Para el vídeo puede dejar la liga en el mismo reporte y subir el vídeo a drive o YouTube. Deberá subir un solo archivo (si es necesario en comprimido) a la plataforma de moodle2, en tiempo y forma. El nombre del archivo deberá estar compuesto por su primer apellido, su primer nombre, sección y número de actividad, por ejemplo: BecerraVioletaD01Act4.pdf. Si se pasa de la fecha de entrega tendrá oportunidad de entrega tardía en Classroom con un menor puntaje.
