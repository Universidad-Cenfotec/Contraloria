# Códigos proyecto contraloría
La ESP32-CAM está programada para capturar imágenes a intervalos regulares, se conecta a la red Wi-Fi utilizando las credenciales proporcionadas y carga la imagen capturada al script de Google Drive configurado en la variable 'myScript'. El script de Google Drive recibe y almacena la imagen, permitiendo su visualización y acceso a través de Google Drive.

**Conectar ESP32-CAM a Google Drive**
**1.** Creación del Script en Google Drive:
Se crea un script en Google Drive utilizando el archivo upload.gs. Este script es esencial para recibir y almacenar las imágenes capturadas por el ESP32-CAM.

**2.** Configuración de Permisos del Script:
Los permisos del script se configuran de manera que sea público, lo que significa que cualquier persona con el enlace puede acceder a él.

**3.** Copia de la URL del Script:
Se copia la URL del script recién creado, que será necesaria para que el ESP32-CAM se comunique con el script y cargue las imágenes en Google Drive.

**4.** Reemplazo de la URL en el Archivo esp32cam-gdrive.ino:
La URL del script de Google se pega en el archivo esp32cam-gdrive.ino, específicamente en la variable llamada 'myScript'. Esto permite al ESP32-CAM saber dónde debe cargar las imágenes capturadas.

**5.** Credenciales de la Red Inalámbrica:
En el mismo archivo esp32cam-gdrive.ino, se deben proporcionar las credenciales de la red inalámbrica. Esto es importante para que el ESP32-CAM pueda conectarse a la red Wi-Fi y transferir las imágenes al script de Google Drive.
