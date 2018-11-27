# Implementación del generador de parámetros en la Zedbaorad
## Módulo XADC Wizard v3.3
### Muestreo de señales de manera simultánea

Se implementa un módulo para el muestreo de dos señales analógicas utilizando el ip XADC Wizard v3.3, el cual hace uso del ADC incluido en la zedboard, el cual es un adc dual de 12-bits, con capacidad de 1 MSPS (mega sample per second), con un ancho de banda ideal de señal de entrada efectiva de 500 kHz (250 kHz en las entradas auxiliares), tiene un rango nominal de entrada de 0V a 1V en modo unipolar ó de -0.5V a 0.5V en modo bipolar.
