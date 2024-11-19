// information Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLWcj7WdIa"
#define BLYNK_DEVICE_NAME "Gas LCD finalTest"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_NODE_MCU_BOARD
#include "BlynkEdgent.h"
int buzzer=5; //D1
int mucCanhbao=500;
BlynkTimer timer;
int timerID1,timerID2;
int mq2_value;
int button=0; //D3
boolean buttonState=HIGH;
boolean runMode=1;//Bật/tắt chế độ cảnh báo
boolean canhbaoState=0;
WidgetLED led(V0);

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(button,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW); //Tắt buzzer
  BlynkEdgent.begin();
  timerID1 = timer.setInterval(1000L,handleTimerID1);
}

void loop() {
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
      if(canhbaoState==0){
        canhbaoState=1;
        Blynk.logEvent("canhbao", String("Cảnh báo! Khí gas=" + String(mq2_value)+" vượt quá mức cho phép!"));
        timerID2 = timer.setTimeout(60000L,handleTimerID2);
      }
      digitalWrite(buzzer,HIGH);
      Blynk.virtualWrite(V3,HIGH);
      Serial.println("Đã bật cảnh báo!");
    }else{
      digitalWrite(buzzer,LOW);
      Blynk.virtualWrite(V3,LOW);
      Serial.println("Đã tắt cảnh báo!");
    }
  }else{
    digitalWrite(buzzer,LOW);
    Blynk.virtualWrite(V3,LOW);
    Serial.println("Đã tắt cảnh báo!");
  }
}
void handleTimerID2(){
  canhbaoState=0;
}
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V2,V4);
}
BLYNK_WRITE(V2) {
  mucCanhbao = param.asInt();
}
BLYNK_WRITE(V4) {
  runMode = param.asInt();
}
