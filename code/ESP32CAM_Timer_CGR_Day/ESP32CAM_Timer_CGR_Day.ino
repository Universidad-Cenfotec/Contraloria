// Adadptado por Tomás de Camino
// Universidad Cenfotec

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "Base64.h"
#include "time.h"

#include "esp_camera.h"

//******* Datos de Red ******
//MIFI
const char* ssid = "your_SSID";           // El SSID de tu red
const char* password = "your_password";  // Tu contraseña de red


// ***************************

//Script para conectar al Google Drive
const char* myDomain = "script.google.com";
String myScript = "/macros/";    //Replace with your own url

String myFilename = "filename=ESP32-CAM.jpg";
String mimeType = "&mimetype=image/jpeg";
String myImage = "&data=";
int waitingTime = 10000;

// Espera 30 segundos a la respuesta de google.

//para tomar la hora del día
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -25200;  // Ajusta esto según tu zona horaria, en segundos (-7 horas)
const int   daylightOffset_sec = 3600; // Ajusta esto si tu zona horaria tiene horario de verano

//Datos de Cámara
#define CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

#define MAX_TRIES 50

const int donepin = 12;  //12 en placas de CENFOTEC , 2 en prototipo
int tries = 0; //intentos de WiFi

void setup() {
  pinMode(donepin, OUTPUT);
  digitalWrite(donepin, LOW);

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);


  while ((WiFi.status() != WL_CONNECTED) && (tries < MAX_TRIES)) {
    delay(500);
    tries++;
  }

  //si no pudo conectarse apaga de un vez
  if (tries >= MAX_TRIES) {
    // Enviar "Done" a timer
    digitalWrite(donepin, HIGH);
    delay(100);
  }

  // Inicializar SNTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);


  int t = 0;
  struct tm timeinfo;
  while(!getLocalTime(&timeinfo)&&(t<20)){
    delay(50);
      t++;
  }

  // Comprobar si la hora actual está entre las 6 de la mañana y las 6 de la tarde
  //sino se desconecta
  if (timeinfo.tm_hour < 5 || timeinfo.tm_hour >= 18) {
      digitalWrite(donepin, HIGH);
      delay(100);
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

  //Cambia controles de cámara
  sensor_t* s = esp_camera_sensor_get();
  //s->set_gain_ctrl(s, 0); // 0 = disable , 1 = enable
  //s->set_exposure_ctrl(s, 0);  // auto-exposure 0 = disable , 1 = enable
  //s->set_agc_gain(s, 1); // set gain manually (0 - 30)
  //s->set_aec_value(s, 10);  // set exposure manually (0-1200)
  //s->set_ae_level(s, -2);


  //Other parameters
  //s->set_brightness(s, 0);     // -2 to 2
  s->set_contrast(s, 2);       // -2 to 2
  s->set_saturation(s, -2);     // -2 to 2
  //s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)
  //s->set_whitebal(s, 1);       // 0 = disable , 1 = enable
  //s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
  //s->set_wb_mode(s, 0);        // 0 to 4 - if awb_gain enabled (0 - Auto, 1 - Sunny, 2 - Cloudy, 3 - Office, 4 - Home)
  //s->set_exposure_ctrl(s, 1);  // 0 = disable , 1 = enable
  //s->set_aec2(s, 1);           // 0 = disable , 1 = enable
  //s->set_ae_level(s, -2);       // -2 to 2
  //s->set_aec_value(s, 0);    // 0 to 1200
  //s->set_gain_ctrl(s, 1);      // 0 = disable , 1 = enable
  //s->set_agc_gain(s, 0);       // 0 to 30
  //s->set_gainceiling(s, (gainceiling_t)0);  // 0 to 6
  //s->set_bpc(s, 0);            // 0 = disable , 1 = enable
  //s->set_wpc(s, 1);            // 0 = disable , 1 = enable
  //s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable
  s->set_lenc(s, 0);           // 0 = disable , 1 = enable
  //s->set_hmirror(s, 0);        // 0 = disable , 1 = enable
  //s->set_vflip(s, 0);          // 0 = disable , 1 = enable
  //s->set_dcw(s, 1);            // 0 = disable , 1 = enable
  //s->set_colorbar(s, 0);       // 0 = disable , 1 = enable

  // Captura la imagen
  // if (WiFi.status() == WL_CONNECTED) {
  saveCapturedImage();
  delay(10);
  //}

  // Enviar "Done" a timer
  digitalWrite(donepin, HIGH);
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

    camera_fb_t* fb = NULL;
    fb = esp_camera_fb_get();
    if (!fb) {
      delay(1000);
      ESP.restart();
      return;
    }

    char* input = (char*)fb->buf;
    char output[base64_enc_len(3)];
    String imageFile = "";
    for (int i = 0; i < fb->len; i++) {
      base64_encode(output, (input++), 3);
      if (i % 3 == 0) imageFile += urlencode(String(output));
    }
    String Data = myFilename + mimeType + myImage;

    esp_camera_fb_return(fb);


    client.println("POST " + myScript + " HTTP/1.1");
    client.println("Host: " + String(myDomain));
    client.println("Content-Length: " + String(Data.length() + imageFile.length()));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println();

    client.print(Data);
    int Index;
    for (Index = 0; Index < imageFile.length(); Index = Index + 1000) {
      client.print(imageFile.substring(Index, Index + 1000));
    }

    long int StartTime = millis();
    while (!client.available()) {
      delay(100);
      if ((StartTime + waitingTime) < millis()) {
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

String urlencode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}
