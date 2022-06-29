/*************************************************************************************
 * download thingspeak library from github 
 *
 * link to download 
 *   https://github.com/mathworks/thingspeak-arduino.git
 *  
 *  paste the below url in the prefrences 
 *  http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *   
 *  go to board managers and change the board name
 * 
 * 
 * 
 * 
 */



#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include<Servo.h>
#include "ThingSpeak.h"
Servo servo;

WiFiClient  client;


unsigned long mychannelnumber = *****; // enter your thingspeak channel number here 
const char * myWriteAPIKey = " ";// enter your thingspeak api here 

int count=0;
int state1=0;
int state2=0;

void setup()
{
  pinMode(16,INPUT);
  pinMode(4,INPUT);
  pinMode(0,INPUT);
  pinMode(2,INPUT);
  pinMode(15,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(115200);
  WiFi.begin("****", "****"); // replace the stars by your wifi name and password 
  ThingSpeak.begin(client);
  servo.attach(5);
}

void loop()
{
  int val1 = digitalRead(16);
  int val2 = digitalRead(4);
  int val3 = digitalRead(0);
  int val4 = digitalRead(2);
  servo.write(180);
  //Serial.println(val);
  if(val1==0){
  servo.write(0);
  }
 if(val2==0&&state1==0)
   {
    count++;
    state1 = 1;
   }
 if(val3==0&&state2==0)
 {
  count++;
  state2=1;
 }
 if(val2==1&&state1==1)
 {
   count--;
   state1=0;
   if(state2==0)
      count=0;
 }
  if(val3==1&&state2==1)
 {
   count--;
   state2=0;
   if(state1==0)
      count=0;
 }
   Serial.println(count);
  if(count<2){
    digitalWrite(15,HIGH);
    digitalWrite(13,LOW);
  }
  if(count==2){
    digitalWrite(13,HIGH);
    digitalWrite(15,LOW);
  }
  ThingSpeak.writeField(mychannelnumber, 1, count, myWriteAPIKey);
  delay(5000);
}
