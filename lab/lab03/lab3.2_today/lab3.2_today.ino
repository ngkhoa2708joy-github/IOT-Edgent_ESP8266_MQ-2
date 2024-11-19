#include <TimeLib.h>
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WidgetRTC.h>
#define BLYNK_PRINT Serial
#define led D7
long nowtime,starttime,stoptime;
WidgetRTC rtc;
WidgetLED appled(V6);
BlynkTimer timer;
 
char auth[] = "GWMyNwYurOX9irzHRfVS4KHfbBad9J_m";
char ssid[] = "TRANTHEBAO";
char pass[] = "27121977";

void clockDisplay(){
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Blynk.virtualWrite(V2, currentTime);
  Blynk.virtualWrite(V1, currentDate); 
}
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass,"sv.bangthong.com",8080);
  rtc.begin();
  timer.setInterval(1000L, clockDisplay);
  pinMode(led,OUTPUT);
}
BLYNK_WRITE(V5){
  TimeInputParam t(param);
  nowtime = ((hour()*3600)+(minute()*60)+second());//thời gian hiện tại
  starttime = (t.getStartHour()*3600)+(t.getStartMinute()*60);//thời gian bắt đầu
  stoptime = (t.getStopHour()*3600)+(t.getStopMinute()*60);//thời gian kết thúc
}
void loop() {
  if(nowtime>=stoptime){
    digitalWrite(led,LOW);
    appled.off();
    }
  else if(nowtime>=starttime){
    digitalWrite(led,HIGH);
    appled.on();
    }
Blynk.run();
timer.run();
}