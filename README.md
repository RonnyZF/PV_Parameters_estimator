# Proyecto de Investigación
# SESLAB TEC 2019

## Colaboradores:
* Ronny Zárate
* Alfonso Chacón
* Kaleb Alfaro
* Carlos Meza
# Estimador de parámetros de **PV**


# Introducción:

Este trabajo es una implementación física del estimador de parámetros de paneles fotovoltaicos. Con este método se puede garantizar computacionalmente los parámetros del modelo de un PV para determinar su nivel de eficiencia instantáneo.


## Esta implemetación consta de 3 secciones:

* **Acoplamiento y sensado de las señales del PV**
* **Muestreo y flujo de procesamiento de los datos**
* **Interfaz de usuario para lectura de los datos**

## Componentes utilizados

| Componentes| | | | |
|-:|-:|-:|-:|-:|
|Zedboard|.|.|.|.|


##  Sensado y acondicionamiento de las señales del PV

En esta etapa se sensan las señales de voltaje y corriente del panel solar las cuales son acondicionadas para la lectura del ADC en la Zedboard, se entrega una señal diferencial variante entre -0.5V a 0.5V.

![Diagrama de bloques de conexión del estimador](https://github.com/RonnyZF/PV_Parameters_estimator/blob/master/Archivos_readme/Top_diagram.jpeg)

## Muestreo y flujo de procesamiento de los datos

Esta sección consta de dos módulos implementados en la Zedboard. Se tiene un primer módulo que muestrea los datos utilizando el ADC de la zedboard, el cual toma muestras de la corriente y el voltaje del panel solar, estos son enviados mediante protocolo AXI4-Stream al segundo módulo el cual recibe los datos entregados por el ADC son almacenados en una interfaz FIFO para su procesamiento matemático, la salida de este módulo se tienen los parámetros θ̂1 y θ̂2 los cuales son disponibles para lectura mediante AXI4-Stream.

![Diagrama de bloques IP implementados](https://github.com/RonnyZF/PV_Parameters_estimator/blob/master/Archivos_readme/Diagrama_zedboard.jpeg)

## Interfaz de usuario para lectura de los datos

Programa de software que cumple la función de interfaz con el usuario para una fácil lectura del comportamiento de los parámetros.
