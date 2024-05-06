# Proceso de Diseño

- El proceso de diseño se explica en el [siguiente video](https://drive.google.com/file/d/1DGaU7ya0ZxTkijEyFO8wcMf-l3KS4jHS/view?usp=sharing)

# Archivos de Diseño

1. Caja_Camara_P1.stl  Caja que contiene la cámara
2. Caja_Camara_P2.stl  Tapa de la caja de cámara
3. Union_Camara_Poste.stl Pieza que sostiene la cámara al poste
4. Visor_Camara.stl Visor que proteje el elnte de lluvia y luz
5. Cubierta_Lente.svg  archivo para corte láser que ptotege el lente del ESP32CAM
6. Anclaje_Techo.stl Pieza que sostiene un techo de zinc al poste

# Recomendaciones para imprimir 3D

- Plástico: PLA MAX
- Pintura exterior esmalte blanco (protección rayos UV)
- Resolución: 0.2mm
- Capas y Paredes: forzar cuatro capas de paredes
- Relleno: 60% con patrón triangular para darle más resistencia
- La impresión tarda aproximadamente 9h25m en una Prusa MK4 en modo impresión rápida

--- 
![](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/camara_completa.JPG)
# Instrucciones de Armado de la Cámara

## Caja de la cámara
- Las instrucciones de armado de la cámara las ueden ver en el [siguiente video](https://drive.google.com/file/d/1R8fjxk--XU2Z1inmcDHXZ_iKdpq5K-TY/view?usp=sharing)
## Incorporar el ESP32 a la caja
- Cambiar el WiFi y direcciónd e Google Drive, siguiendo estas instrucciones
- El ESP32, se conecta a la placa TPL5110, a través de el adaptador de plástico como se muestra en la siguientes fotos
  ![ESP32 Clip](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/esp32_clip.JPG)
  ![](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/esp32_clip2.JPG)
- Una vez conectado el ESP32 a la placa, se conectan las baterías, seinserta en la cámara, con cuidado, como se muestra en las siguientes fotografías
![](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/esp32_camara.JPG)
![](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/esp32_camara2.JPG)
- Una vez cerrada la cámara probar que suba las fotos.

## Modificación de los intervalos de fotografía
- Para modificar en intervalo en que el ESP32 toma las fotos, seguir las instrucciones de este video.

## Cargado de baterías

- Para el cargado de baterías seguir las instrucciones del siguiente video


---
# Historial de Diseño

## Versión 1

Problemas:
- Tapa difícil de colocar
- Cavidad permite pocos tipos de batería
- Se necesita dar vuelta a la imágen
- "Lente" difícil de instalar, y no se puede reparar.
- No resiste golpes muy fuertes

## Versión 2

Problemas:
- Lente expuesto se moja fácilmente
- Acrílico genera reflejos que hace que la foto se sobre exponga
- Union a anclaje hace que cámara quede muy separada del techo

Todo estos problemas han sido corregidos en la verisón final publicada
