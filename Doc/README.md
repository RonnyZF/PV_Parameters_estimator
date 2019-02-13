## Guía para crear el proyecto en Vivado HLS

### Creación del proyecto estimador

- Clone el repositorio de github correspondiente al proyecto

      git clone https://github.com/RonnyZF/PV_Parameters_estimator

- Abra vivado hls con

      source /opt/Xilinx/Vivado/2017.4/settings64.sh &&  vivado_hls

    Si tiene instalada otra versión de vivado debe cambiarla en el path por su versión correspondiente, sin embargo se recomienda usar dicha versión debido a cambios en la implementación de la función estimador (mayor uso de DSP) si se realiza en una versión anterior de vivado_hls.

- Cree un nuevo proyecto, nómbrelo Estimador y seleccionar el path donde clonó el repositorio

      ...PATH/PV_Parameters_estimator

- Designe como top función **wrapper_fixed_estimator** y agregue con añadir archivos el **estimador.cpp** ubicado en

      ...PATH/PV_Parameters_estimator/Zedboard/Estimador/estimador.cpp

- Agregue el archivo de testbench llamado **tb_estimador.cpp** ubicado en

      ...PATH/PV_Parameters_estimator/Zedboard/Testbench/tb_estimador.cpp

- En el espacio para configuración del clock, deje el periodo en 10 y Uncertainty en 3 y seleccione en la sección **Part Selection** la **Zedboard Zynq Evaluation and Development Kit** y de finalizar.

- En este punto es posible correr el testbench y la Synthesis.

**Nota:** Si tiene problemas para correr la simulación en C puede cambiar el compilador de gcc a clang

### implementación del módulo para cálculo de logaritmo basado en log2

- Cree un nuevo proyecto, nómbrelo Calculo_log2 y seleccionar el path donde clonó el repositorio

        ...PATH/PV_Parameters_estimator

- Designe como top función **fixed_log** y agregue con añadir archivos el **Ln_using_log2.cpp** ubicado en

      ...PATH/PV_Parameters_estimator/Zedboard/Library/Ln_using_log2.cpp

- Agregue el archivo de testbench llamado **tb_ln_using_log2.cpp** ubicado en

      ...PATH/PV_Parameters_estimator/Zedboard/Testbench/tb_ln_using_log2.cpp

- En el espacio para configuración del clock, deje el periodo en 10 y Uncertainty en 3 y seleccione en la sección **Part Selection** la **Zedboard Zynq Evaluation and Development Kit** y de finalizar.

- En este punto es posible correr el testbench y la Synthesis.

**Nota:** Si tiene problemas para correr la simulación en C puede cambiar el compilador de gcc a clang

### implementación del módulo para cálculo de logaritmo basado en Series de Taylor

- Cree un nuevo proyecto, nómbrelo Calculo_log_taylor y seleccionar el path donde clonó el repositorio

        ...PATH/PV_Parameters_estimator

- Designe como top función **Fixed_ln_taylor_series** y agregue con añadir archivos el **Ln_taylor_series.cpp** ubicado en

      ...PATH/PV_Parameters_estimator/Zedboard/Library/Ln_taylor_series.cpp

- Agregue el archivo de testbench llamado **tb_ln_taylor_series.cpp** ubicado en

      ...PATH/PV_Parameters_estimator/Zedboard/Testbench/tb_ln_taylor_series.cpp

- En el espacio para configuración del clock, deje el periodo en 10 y Uncertainty en 3 y seleccione en la sección **Part Selection** la **Zedboard Zynq Evaluation and Development Kit** y de finalizar.

- En este punto es posible correr el testbench y la Synthesis.

**Nota:** Si tiene problemas para correr la simulación en C puede cambiar el compilador de gcc a clang
