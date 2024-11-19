
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLbb-IugCv"
#define BLYNK_DEVICE_NAME "nhiệt độ và độ ẩm"
#define BLYNK_AUTH_TOKEN "eyTsH_F5ckl4lPD_0gWI2RxAc3Ahqe1R"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
WidgetLED led1(V0);
char auth[] = "eyTsH_F5ckl4lPD_0gWI2RxAc3Ahqe1R";
char ssid[] = "TRANTHEBAO";
char pass[] = "27121977";

void sendSensor()
{
  if (led1.getValue()) {
    led1.off();
  } else {
    led1.on();
  }
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t); 
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}

