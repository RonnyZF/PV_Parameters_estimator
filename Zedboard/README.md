# Implementación del generador de parámetros en la Zedbaorad
## Módulo XADC Wizard v3.3
### Muestreo de señales de manera simultánea

Se implementa un módulo para el muestreo de dos señales analógicas utilizando el ip XADC Wizard v3.3, el cual hace uso del ADC incluido en la zedboard, el cual es un adc dual de 12-bits, con capacidad de 1 MSPS (mega sample per second), con un ancho de banda ideal de señal de entrada efectiva de 500 kHz (250 kHz en las entradas auxiliares), tiene un rango nominal de entrada de 0V a 1V en modo unipolar ó de -0.5V a 0.5V en modo bipolar.

![Diagrama de bloques XADC](https://github.com/RonnyZF/PV_Parameters_estimator/blob/master/Archivos_readme/xadc_module.jpeg)

## Módulo HLS Estimador
### Estimación de los parámetros θ̂1 y θ̂2

Para la estimación de los parámetros θ̂1 y θ̂2 se reciben los datos provenientes del XADC mediante AXI4-Stream en una interfaz FIFO, seguidamente son separados en dos colas para los correspondientes valores de voltaje y corriente, dichos valores son convertidos nuevamente a los valores iniciales censados directamente del panel, para la señal de corriente se aplica una operación de logaritmo, que es necesaria para que luego dichos pares de valores sean computados en el estimador, a la salida del estimador se tiene los parámetros los cuales se pueden leer mediante AXI4-Lite

![Flujo de datos módulo estimador](https://github.com/RonnyZF/PV_Parameters_estimator/blob/master/Archivos_readme/hls_ip.jpeg)
