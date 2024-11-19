
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define BLYNK_PRINT Serial
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();


  if (isnan(h)|| isnan(t)){
    Serial.println("Failed to read from DHT sensor"); 
    return;
  }
  
  Serial.println(t);
  Serial.println(h);
  
  lcd.setCursor(11,0);   
  lcd.print(h);
  lcd.setCursor(11,1);  
  lcd.print(t); 
  dht.begin();
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.clear();         
  lcd.backlight();      
  lcd.setCursor(0,0);  
  lcd.print("Do am:");
  lcd.setCursor(0,1);   
  lcd.print("Nhiet do:"); 
}

void loop() {
   sendSensor();
   delay(500);
}
