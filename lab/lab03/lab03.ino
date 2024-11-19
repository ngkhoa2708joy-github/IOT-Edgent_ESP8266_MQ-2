/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPLGLGdoVGR"
#define BLYNK_DEVICE_NAME "3 led"
#define BLYNK_AUTH_TOKEN "kpkpvWMtGC4tNzVM00cKtu6dA65ZyhOq"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "kpkpvWMtGC4tNzVM00cKtu6dA65ZyhOq";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Nhựt's Galaxy A31";
char pass[] = "nhut3011";


#define ledr D1
#define ledy D2
#define ledg D3
int button1, button2, button3;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
}

BLYNK_WRITE(V11)
{
  button1 = param.asInt();
  if(button1 == 1){
    digitalWrite(ledr, HIGH);
  }
  else{
    digitalWrite(ledr,LOW);
  }
}

BLYNK_WRITE(V12)
{
  button2 = param.asInt();
  if(button2 == 1){
    digitalWrite(ledy, HIGH);
  }
  else{
    digitalWrite(ledy,LOW);
  }
}

BLYNK_WRITE(V13)
{
  button3 = param.asInt();
  if(button3 == 1){
    digitalWrite(ledg, HIGH);
  }
  else{
    digitalWrite(ledg,LOW);
  }
}

void loop()
{
  Blynk.run();
}

