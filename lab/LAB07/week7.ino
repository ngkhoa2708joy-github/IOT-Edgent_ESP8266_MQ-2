#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
OneWire giaotiep1day(2);
DallasTemperature cb(&giaotiep1day);
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLuD4EbT9p"
#define BLYNK_DEVICE_NAME "bai2"
#define BLYNK_AUTH_TOKEN "hKfxqODn1zAqNItmMyfFRrBepMh4Wz5c"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_NODE_MCU_BOARD
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
int mucCanhbao=50;
BlynkTimer timer;
LiquidCrystal_I2C lcd(0x3F,16,2);
int timerID1,timerID2;
float nhietdo=0;
int button=0; //D3
boolean buttonState=HIGH;
boolean runMode=1;//Bật/tắt chế độ cảnh báo
boolean canhbaoState=0;
WidgetLED led(V0);

char auth[] = "hKfxqODn1zAqNItmMyfFRrBepMh4Wz5c";
char ssid[] = "Redmi Note 10";
char pass[] = "hongan123";

void setup()
{
  cb.begin();
  Serial.begin(115200);
  delay(100);
  Blynk.begin(auth, ssid, pass);
  timerID1 = timer.setInterval(1000L,handleTimerID1);
}

void loop() {
  timer.run();
  if(digitalRead(button)==LOW){
    if(buttonState==HIGH){
      buttonState=LOW;
      runMode=!runMode;
      Serial.println("Run mode: " + String(runMode));
      Blynk.virtualWrite(V4,runMode);
      delay(200);
    }
  }else{
    buttonState=HIGH;
  }
}
void handleTimerID1(){
 cb.requestTemperatures();
 nhietdo=cb.getTempCByIndex(0);
 Serial.println(nhietdo);
  Blynk.virtualWrite(V1,nhietdo);
  if(led.getValue()) {
    led.off();
  } else {
    led.on();
  }

  lcd.init();
  lcd.clear();         
  lcd.backlight();      
  lcd.setCursor(1,0);  
  lcd.print("Nhiet do");
  lcd.setCursor(10,0);   
  lcd.print(nhietdo);
  lcd.setCursor(1,1);   
  lcd.print("Canh bao"); 
  lcd.setCursor(10,1);  
  lcd.print(mucCanhbao); 
  
  if(runMode==1){
    if(nhietdo>mucCanhbao){
      if(canhbaoState==0){
        canhbaoState=1;
        Blynk.logEvent("canh_bao", String("Cảnh báo! nhiet do =" + String(nhietdo)+" vượt quá mức cho phép!"));
         lcd.init();
        lcd.clear();         
        lcd.backlight();      
        lcd.setCursor(1,0);  
        lcd.print("Nhiet do");
        lcd.setCursor(1,1);   
        lcd.print("vuot qua muc"); 
        timerID2 = timer.setTimeout(600L,handleTimerID2);
      }

      Blynk.virtualWrite(V2,HIGH);
      Serial.println("Đã bật cảnh báo!");
    }else{

      Blynk.virtualWrite(V2,LOW);
      Serial.println("Đã tắt cảnh báo!");
    }
  }else{
    Blynk.virtualWrite(V2,LOW);
    Serial.println("Đã tắt cảnh báo!");
  }
}
void handleTimerID2(){
  canhbaoState=0;
}
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V2,V4);
}
BLYNK_WRITE(V3) {
  mucCanhbao = param.asInt();
}
BLYNK_WRITE(V4) {
  runMode = param.asInt();
}
