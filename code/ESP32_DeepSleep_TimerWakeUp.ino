/*
Tomás de Camino Beck
Universidad Cenfotec
Ejemplo sencillo de Sleep en ESP32
*/

#define uS_TO_M_FACTOR 60000000ULL  /* conversion de microsegundos a minutos */
#define TIME_TO_SLEEP  1        /* tiempo en minutos de sleep */

//Almacena variable en el reloj
RTC_DATA_ATTR int bootCount = 0;


void setup(){
  Serial.begin(115200);
  delay(1000);

  //Conteo de boots
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
 
  //Configura para timer wakeup cada TIME_TO_SLEEP Minutos
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_M_FACTOR);

  Serial.println("Turn OFF");
  Serial.flush(); 
  //Inicia Deep Sleep
  esp_deep_sleep_start();

}

void loop(){
  //nunca corre
}
