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

