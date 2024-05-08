![camara IoT](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/header.JPG)
# Proyecto Fiscalización de Obra Pública IoT

Este es el resultado de un proyecto de investigación en coordinación con la Contraloría General de la República de Costa Rica y la cooperación alemana GIZ, para el desarrollo de cámaras IoT de bajo costo, que permitan monitorear y fiscalizar obras de construcción pública, incorporando ideas novedosas para el desarrollo de tecnología local y de bajo costo, además de la utilización de Inteligencia artificial para identificación de patrones de progreso de construcción pública. Este es el repositorio con todos los resultados del proyecto, y que permite su reproducción abierta.

El repositorio del piloto realizado por la contraloría se encuentra en este link:
https://github.com/cgrcostarica/fiscalizacion_infra_IA

## Organización del repositorio
- "code" códigos para los dispositivos utilizados. e instrucciones para programar el microcontrolador
- "design" Archivos 2D y 3D de diseño de estructuras de fabricación y soporte del sistema. Video instruccional de ensamblado de la cámara
- "documentos" Documentación de respaldo (presentaciones, reportes técnicos, documentos de soporte)
- "imagenes" conteien las imágenes que se utilizan en este repositorio
- "placa_tpl" detalles del diseño de la placa TPL, y los esquemas para fabricación


Estes es un proyecto realizado por **Universidad Cenfotec**, en cooperación con la Contraloría General de la República, con fondos de la GIZ.

Aunque exiten tecnologías en el mercado que podría cumplir esta función, este proyecto va dentro de la filosofía "Nuestros para fabricar, adaptar, reparar y crecer", es decir, la intencióne s crear tecnología sobre la cual se pueda evolucionar, y cuyo mejoramiento dependa de nuestras propias acciones y no de la capacidad de un proveedor.

## Investigadores Principales

Dr. Tomás de Camino Beck

Dr. Luis Carlos Naranjo

## Investigadores de apoyo

M.Sc. Rodrigo Herrera

# Asistentes de Investigación y Fabricación

Estudiante Jeffry Valverde

![Camaras Instaladas](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/footer.JPG)

# Etapa de Inteligencia Artificial

**Objetivo:** Crear un modelo de inteligencia artificial que permita realizar la detección de objetos en las imagenes captadas en la etapa de IOT relacionadas al proyecto de contrucción de la Escuela de Pocosi. 

## Investigadores Principales
M.Sc. Rodrigo Herrera

## Asistentes de Investigación y Desarrollo
Gabriel Lobo

Dr. Tomás de Camino Beck

La documentación necesaria de la etapa de IA se encuentra en la carpeta "Documentos Etapa IA-GIZ-CENFOTEC", dentro de la misma contiene la siguiente organización.
- "Códigos" :
  - Los archivos del docker que va en el proceso de producción *sin los modelos
  - El proceso de entrenamiento
  - Autenticación de Google Drive
- "Documentación"
  - La documentación necesaria para todos los procesos
- "Imagenes y Etiquetas
  - Etiquetas necesarias para llevar a cabo el proceso de entrenamiento y evaluación
  - Ejemplo de 5 imagenes
- "Modelos"
  - Contiene un txt que indica donde se puede encontrar los modelos
 
## Resultados de Modelos

Se han compartido 1 modelo principal. 
 - Modelo_1_29
 - - Metricas
   - Promedio de IoU: 82.7%
   - Sensitividad: 85.4% (Equivale a las predicciones verdaderamente predichas)

### Ejemplo de Inferencia 1
![Ejemplo de Inferencia](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/Ejemplo_Inferencia.jpg) 


### Ejemplo de Inferencia 2
En este ejemplo se puede observar 2 cajas de diferente color en cada objeto. 

- La caja Azul es la caja de la etiqueta real

- La caja Roja es la caja de la predicción realizada por el modelo

Fácilemente se puede apreciar la efectividad del modelo en hacer su trabajo de predicción. 
![Ejemplo 2 de Inferencia](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/Ejemplo_Inferencia2.jpg)


*Se debe tomar en cuenta que este modelo esta entrenado solamente con imagenes captadas por las camaras realizadas en la etapa de IoT para el proyecto de construcción de la Escuela de Pocosí, por ende este modelo esta sobre-entrenado para realizar inferencias para este proyecto, en caso de que se ponga el modelo a realizar inferencias de otras imagenes, o proyectos diferentes, es posible que el modelo no sea lo esperado en su eficiencia.
