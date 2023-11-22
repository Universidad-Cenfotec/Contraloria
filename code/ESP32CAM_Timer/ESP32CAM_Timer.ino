// Adadptado por Tomás de Camino Beck
// Universidad Cenfotec

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "Base64.h"

#include "esp_camera.h"

//******* Datos de Red ******

const char* ssid     = "LIB-4416434";   // El SSID de tu red
const char* password = "kSLNbtsFTE3aWAfR";   // Tu contraseña de red

// ***************************



//Script para conectar al Google Drive
const char* myDomain = "script.google.com";
String myScript = "/macros/s/AKfycbwXVIt71tL67ctq4JTQdN3dRUDulb6BKs7wyVt7v_e5rSqyPcAn7o-Hs3OuT2gw_GEv/exec";    // Remplaza con tu propio URL
String myFilename = "filename=ESP32-CAM.jpg";
String mimeType = "&mimetype=image/jpeg";
String myImage = "&data=";
int waitingTime = 10000; //Wait 30 seconds to google response.

// Espera 30 segundos a la respuesta de google.


//Datos de Cámara
#define CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22


const int donepin = 4;

void setup()
{
  pinMode(donepin, OUTPUT);
  digitalWrite(donepin,LOW);
  
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //Configuración de Cámara
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_VGA;  // UXGA|SXGA|XGA|SVGA|VGA|CIF|QVGA|HQVGA|QQVGA
  config.jpeg_quality = 10;
  config.fb_count = 1;
  

  //Inicializa cámara
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    delay(300);
    ESP.restart();
  }

      // Captura la imagen
  saveCapturedImage();
  delay(10);

  // Enviar "Done" a timer
  digitalWrite(donepin,HIGH);
  delay(100);

}


void loop() {
  //no corre
}

// ######################
void saveCapturedImage() {
  WiFiClientSecure client;
  client.setInsecure();
  
  if (client.connect(myDomain, 443)) {

    camera_fb_t * fb = NULL;
    fb = esp_camera_fb_get();  
    if(!fb) {
      delay(1000);
      ESP.restart();
      return;
    }
  
    char *input = (char *)fb->buf;
    char output[base64_enc_len(3)];
    String imageFile = "";
    for (int i=0;i<fb->len;i++) {
      base64_encode(output, (input++), 3);
      if (i%3==0) imageFile += urlencode(String(output));
    }
    String Data = myFilename+mimeType+myImage;
    
    esp_camera_fb_return(fb);
    
    
    client.println("POST " + myScript + " HTTP/1.1");
    client.println("Host: " + String(myDomain));
    client.println("Content-Length: " + String(Data.length()+imageFile.length()));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println();
    
    client.print(Data);
    int Index;
    for (Index = 0; Index < imageFile.length(); Index = Index+1000) {
      client.print(imageFile.substring(Index, Index+1000));
    }
    
    long int StartTime=millis();
    while (!client.available()) {
      delay(100);
      if ((StartTime+waitingTime) < millis()) {
        // Si no tiene respuesta, tal vez necesite un valor mayor de waitingTime
        break;
      }
    } 
    //while (client.available()) {
      //Serial.print(char(client.read()));
    //}  
  } else {         
    //Serial.println("Connected to " + String(myDomain) + " failed.");
  }
  client.stop();
}

String urlencode(String str)
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
}
