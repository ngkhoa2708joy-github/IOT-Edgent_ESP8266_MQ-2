// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLWcj7WdIa"
#define BLYNK_DEVICE_NAME "Gas LCD finalTest"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_NODE_MCU_BOARD
#include "BlynkEdgent.h"
#include <MQ2.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16,2);

int Analog_Input = A0;
int lpg, co, smoke;
MQ2 mq2(Analog_Input);

int mucCanhbao=500;
BlynkTimer timer;
int timerID1,timerID2;
int mq2_value;
int button=0; //D3
boolean buttonState=HIGH;
boolean runMode=1;//Bật/tắt chế độ cảnh báo

WidgetLED led(V0);

void setup()
{
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  mq2.begin();
  delay(100);
  pinMode(button,INPUT_PULLUP);
  BlynkEdgent.begin();
  timerID1 = timer.setInterval(1000L,handleTimerID1);
}

void loop() {
  float* values= mq2.read(true);
  
  lpg = mq2.readLPG();
  co = mq2.readCO();
  smoke = mq2.readSmoke();

  lcd.setCursor(0,0);
  lcd.print("LPG:");
  lcd.print(lpg);
  lcd.print(" CO:");
  lcd.print(co);
  lcd.setCursor(0,1);
  lcd.print("SMOKE:");
  lcd.print(smoke);
  lcd.print(" PPM");
  delay(1000);

  BlynkEdgent.run();
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
  mq2_value = analogRead(A0);
  Blynk.virtualWrite(V1,mq2_value);
  if(led.getValue()) {
    led.off();
  } else {
    led.on();
  }
  if(runMode==1){
    if(mq2_value>mucCanhbao){
      Blynk.logEvent("canhbao", String("!!! WARNING !!! Gas emissions = " + String(mq2_value)+ " is over premission!"));
      Serial.println("!!! WARNING !!! Gas emissions = " + String(mq2_value)+ " is over premission!");
      delay(5000);
    }else{
      Serial.println("-- Mode ON => Normal gas emissions");
      delay(3000);
    }
  }
  else{
    Serial.println("-- Mode: warning is TURNING OFF, be safe--");
    delay(2000);
  }
}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V3,V4);
}
BLYNK_WRITE(V3) {
  mucCanhbao = param.asInt();
}
BLYNK_WRITE(V4) {
  runMode = param.asInt();
}
