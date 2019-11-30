# Turino
*Turing Machine + Arduino = Turino*

## Descripción
Implementación de la Máquina de Turing con el uso de Arduino. Se utilizó una tira LED RGB para representar la cinta y
una línea de LED que representan el cursor. Por defecto se trabaja unicamente con los símbolos *0*, *1* y *blank*.

Más información sobre la Máquina de Turing [aquí](https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/turing-machine/one.html)
o ver PDF.

Consta de direfentes etapas:

- **Ingresar cantidad de estados**

  Se puede definir hasta un máximo de 20 estados. Además de estos estados se tienen dos más añadidos por defecto: aceptación y 
  rechazo, que son parte de la definición de la máquina. Ver PDF para más información.
  
  
- **Ingresar función de transición**

  Para cada estado y cada símbolo, se debe ingresar su función de transición de la forma:
  
  ``` 
  q00, 0 -> 1 L A
            w m n
  ```
  Para este caso, se expresa que para el estado `q00`, cuando lea `0` de la cinta, escribirá en esa celda el símbolo `1` (w),
  se desplazará hacia la izquierda (m), y cambiará al estado de aceptación `A`.
  
- **Ingresar datos a la cinta**

  Se permite desplazar el cursor por la cinta y cambiar el valor donde este se encuentre. Se utiliza el color blanco
  para representar un *0*, el color morado para *1* y LED apagado para *blank*.
  
- **Ingresar estado inicial**

  Se necesita de un estado inicial para que el procesamiendo pueda comenzar.
  
- **Procesamiento**

  Se observará visualmente en los LED (cursor) y la tira LED (cinta), el comportamiento de la función de transición ingresada.
  
- **Finalización**

  Una vez que el estado actual `q` alcance el estado de aceptación `A` o el de rechazo `R`, se mostrará en la pantalla en qué
  estado se finalizó el procesamiento. Tomar en cuenta que si existe algun error en la función de transición, la máquina podría
  nunca terminar el procesamiento, que es un comportamiento válido.
  
  ## Circuito
  La lista de materiales y la configuración del circuito pueden consultarse [aquí](https://www.tinkercad.com/things/6LapaImMSVQ-circuito-maquina-turing/).
  
  ##Demostración
  Una demostración en video disponible [aquí](https://youtu.be/SVJ2mKYP-Xs)
  
