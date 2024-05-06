# Códigos proyecto contraloría

El código ESP32CAM_Timer_CGR_Day.ino proporcionado realiza varias operaciones con un módulo de cámara ESP32CAM, culminando en el envío de una imagen a Google Drive. Una característica notable es el uso de `digitalWrite(donepin, HIGH)`, que se emplea para indicar la finalización de un proceso, activando un temporizador que apaga el controlador. A continuación, se detalla cómo se integra esta función dentro del flujo de trabajo del código:

1. **Establecimiento de la conexión WiFi**:
   - El ESP32 intenta conectarse a la red WiFi especificada. Si no logra conectarse dentro de un número máximo de intentos (`MAX_TRIES`), se considera que ha fallado.
   - Al fallar, ejecuta `digitalWrite(donepin, HIGH)` para indicar que el proceso ha terminado y activa un temporizador externo, que eventualmente apaga el controlador.

2. **Sincronización de tiempo y verificación de horario**:
   - Después de establecer la conexión WiFi, el ESP32 sincroniza su reloj con un servidor NTP.
   - Verifica si la hora actual está fuera del rango establecido (antes de las 5 a.m. o después de las 6 p.m.). Si es así, se activa el temporizador externo mediante `digitalWrite(donepin, HIGH)` para apagar el dispositivo.

3. **Inicialización y configuración de la cámara**:
   - Se configura y activa la cámara. Si la inicialización falla, el sistema se reinicia.
   - Al finalizar la captura y el envío de la imagen, se activa nuevamente el temporizador externo con `digitalWrite(donepin, HIGH)`, indicando que el proceso ha concluido.

4. **Función `saveCapturedImage()`**:
   - Realiza la captura de la imagen, la codificación en base64 y la envía a Google Drive.
   - Tras enviar la imagen, se activa el temporizador externo con `digitalWrite(donepin, HIGH)` para indicar el fin del proceso.

5. **Apagado del sistema**:
   - Cada vez que se llama a `digitalWrite(donepin, HIGH)`, se señala a un circuito externo (probablemente un temporizador o un controlador de potencia) para que inicie el proceso de apagado del ESP32.
  
¡Claro! Aquí tienes un conjunto básico de instrucciones para programar un ESP32-CAM utilizando el Arduino IDE:

---
# Cambio de SSID y Password para red MiFi/WiFi

Para cambiar el acceso WiFi en el código proporcionado, sigue estos pasos:

1. **Abre el Código en el Arduino IDE:**
   - Abre el Arduino IDE en tu ordenador.
   - Copia y pega el código proporcionado en este GitHub en una nueva ventana del Arduino IDE.


2. **Edita la Información de la Red:**
   - Reemplaza el SSID y la contraseña con los de tu red WiFi. Por ejemplo:

   ```cpp
   const char* ssid = "nombre_de_tu_red_wifi";
   const char* password = "tu_contraseña_wifi";
   ```

5. **Guarda y Carga el Código:**
   - Guarda los cambios en el código.
   - Conecta tu ESP32-CAM al ordenador.
   - Selecciona el puerto adecuado y la placa ESP32-CAM en el Arduino IDE.
   - Haz clic en el botón "Upload" para cargar el código modificado en tu ESP32-CAM.



---

# Crear acceso para subir fotos a Google Drive

### 1. Crear el Acceso a Google Drive:

#### 1.1. Crear una Carpeta en Google Drive:
   - Abre Google Drive en tu navegador web.
   - Crea una nueva carpeta donde se guardarán las imágenes que envíe tu ESP32-CAM.

#### 1.2. Obtener el ID de la Carpeta:
   - Haz clic derecho en la carpeta que acabas de crear y selecciona "Obtener enlace".
   - Copia el ID de la carpeta de la URL. El ID de la carpeta es la parte de la URL después de `/folders/`.

#### 1.3. Crear un Nuevo Proyecto en Google Apps Script:
   - Visita el [Editor de Google Apps Script](https://script.google.com/) y crea un nuevo proyecto.

#### 1.4. Escribir el Script en Google Apps Script:
   - En el editor de scripts, copia y pega el siguiente código JavaScript:

   ```javascript
   function doPost(e) {
     var folderId = "ID_de_tu_Carpeta_en_Google_Drive";
     var folder = DriveApp.getFolderById(folderId);
     var blob = e.postData.getBlob();
     var file = folder.createFile(blob);
     return ContentService.createTextOutput("Archivo guardado: " + file.getName());
   }
   ```

   - Reemplaza `"ID_de_tu_Carpeta_en_Google_Drive"` con el ID de la carpeta que obtuviste anteriormente.

#### 1.5. Publicar el Script:
   - Haz clic en `Editar` y selecciona `Desplegar como web app`.
   - En la ventana emergente, elige `Quien tiene acceso a la aplicación: Cualquier persona, incluso anónimos`.
   - Haz clic en `Desplegar` y luego en `OK`.
   - Copia el URL que se genera, lo necesitarás más adelante.

### 2. Modificar el Código para tener Acceso:

#### 2.1. Configurar los Datos de Red WiFi:
   - Abre el código en C/C++ de tu ESP32-CAM.
   - Busca la sección "Datos de Red" y cambia los valores de `ssid` y `password` con los de tu red WiFi:

   ```cpp
   //******* Datos de Red ******
   const char* ssid = "nombre_de_tu_red_wifi";       // El SSID de tu red
   const char* password = "tu_contraseña_wifi";  // Tu contraseña de red
   // ***************************
   ```

   - Sustituye `"nombre_de_tu_red_wifi"` y `"tu_contraseña_wifi"` por el nombre de tu red WiFi y tu contraseña respectivamente.

#### 2.2. Configurar el Script de Google Apps Script:
   - Busca la sección donde se define `myDomain` y `myScript`.
   - Reemplaza `myScript` con el URL del script de Google Apps Script que generaste anteriormente.

   ```cpp
   const char* myDomain = "script.google.com";
   String myScript = "/macros/s/TU_ID_EXEC";    // Reemplaza con tu propio URL
   ```

   - Reemplaza `"TU_ID_EXEC"` con el ID de ejecución que obtuviste del URL del script.

--- 

# Ajuste de los intervalos de tiempo

- Los intervalos en los que se toman la fotografías se ajustan físicamente en la placa TPL, regulando el peqieño potenciómetro de la placa TPL, como se muestra en la siguiente foto.
![](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/Ajuste_TPL1.JPG)

- Cuando el potenciómetro está completamente a la izquierda el intervalo de tiempo es de aproximadamente 2 horas, mientras que cuando está completamente a la derecha, el intervalo es de menos de 1 minuto.  Para efectos del proyecto (intervalo de 10 min), se cooca el potenciómetri alrededor de la 1 del reloj, como se ven en la siguiente foto.

![](https://github.com/Universidad-Cenfotec/Contraloria/blob/main/imagenes/Ajuste_TPL2.JPG)

---



# Instrucciones generales de programación de Placa ESP32-CAM

1. **Instalar el Arduino IDE:**
   - Descarga e instala la última versión del Arduino IDE desde el sitio web oficial: https://www.arduino.cc/en/software.

2. **Instalar el Soporte para ESP32 en el Arduino IDE:**
   - Abre el Arduino IDE.
   - Ve a `File (Archivo) > Preferences (Preferencias)`.
   - En el campo "Additional Board Manager URLs (URLs Adicionales del Gestor de Placas)", añade la siguiente URL: `https://dl.espressif.com/dl/package_esp32_index.json`.
   - Haz clic en "OK".
   - Ve a `Tools (Herramientas) > Board (Placa) > Boards Manager (Gestor de Placas)`.
   - Busca "esp32" y pulsa en "Install (Instalar)" para instalar el soporte para ESP32.

3. **Seleccionar la Placa ESP32-CAM:**
   - Ve a `Tools (Herramientas) > Board (Placa)` y selecciona `ESP32 Wrover Module`.

4. **Configurar las Opciones de la Placa:**
   - Ve a `Tools (Herramientas)` y ajusta las siguientes opciones según sea necesario:
     - `Upload Speed (Velocidad de Subida)`: 115200 baudios (o la velocidad de subida que mejor funcione para tu configuración).
     - `Flash Frequency (Frecuencia de Flash)`: 40 MHz.
     - `Flash Mode (Modo de Flash)`: QIO.
     - `Partition Scheme (Esquema de Partición)`: Huge APP (3MB No OTA/1MB SPIFFS).

5. **Conectar el ESP32-CAM a tu Ordenador:**
   - Conecta tu ESP32-CAM al ordenador utilizando un cable micro-USB.

6. **Configurar el Arduino IDE para la Comunicación con el ESP32-CAM:**
   - Si es la primera vez que utilizas el ESP32-CAM con tu ordenador, es posible que necesites instalar los controladores correspondientes. En la mayoría de los casos, el sistema operativo los instalará automáticamente, pero si experimentas problemas de comunicación, puedes buscar los controladores en línea.

7. **Cargar un Ejemplo o Escribir Tu Propio Código:**
   - Ve a `File (Archivo) > Examples (Ejemplos)` y selecciona un ejemplo para comenzar, como `CameraWebServer` o `CameraWebServer.ino`.
   - O bien, escribe tu propio código en el Arduino IDE.

8. **Modificar el Código (si es necesario):**
   - Si estás utilizando un ejemplo, puedes necesitar modificar ciertas partes del código, como la configuración del Wi-Fi (SSID y contraseña) para que coincida con tu red Wi-Fi.

9. **Compilar y Subir el Código:**
   - Haz clic en el botón "Upload (Subir)" en la esquina superior izquierda del Arduino IDE.
   - Espera a que el código se compile y se suba al ESP32-CAM.

10. **Verificar la Ejecución:**
    - Una vez que la carga haya finalizado correctamente, abre el Monitor Serie (`Tools (Herramientas) > Serial Monitor (Monitor Serie)`) para ver la salida del ESP32-CAM.
    - Si has cargado un ejemplo de cámara web, deberías poder acceder a la dirección IP del ESP32-CAM desde un navegador web y ver la transmisión de la cámara.



