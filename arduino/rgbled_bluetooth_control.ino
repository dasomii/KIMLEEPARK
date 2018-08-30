#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 2); //arduino pin 2:rx 3:tx

int led_H = 5;  //white
int led_W = 6;  //warm white
int led_R = 9;  //red
int led_G = 10; //green
int led_B = 11; //blue

int H, W, R, G, B;

int leds[] = {5,6,9,10,11};
int brightness = 0;
int i;
char input = 'a';

void fadeIn(int pin, int brightness){
  for(i=0; i<brightness; i++)
  {
    analogWrite(pin, i);
    delay(100);
  }
}

void fadeOut(int pin, int brightness){
  for(i=brightness; i>=0; i--)
  {
    analogWrite(pin, i);
    delay(100);
  }
}

void setup() {
  for(i=0; i<sizeof(leds); i++){
    pinMode(leds[i], OUTPUT);
  }
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  if(BTSerial.available()){
    input = BTSerial.read();
    Serial.write(input);
    Serial.write('\n');
  }
  if(Serial.available())
    BTSerial.write(Serial.read());

  if(input == '0'){
    Serial.println("all turn off");
    for(i=0; i<sizeof(leds); i++){
      analogWrite(leds[i], 0);
    }
    H = 0;
    W = 0;
    R = 0;
    G = 0;
    B = 0;  
  }

  if(input == '1'){
    Serial.println("white 100");
    fadeIn(led_H, 100);
    fadeOut(led_W, W);
    fadeOut(led_R, R);  
    fadeOut(led_G, G);  
    fadeOut(led_B, B); 
    H = 100;
    W = 0;
    R = 0;
    G = 0;
    B = 0;
  }
  
  if(input == '2'){
    Serial.println("white 255");
    fadeIn(led_H, 255);
    fadeOut(led_W, W);
    fadeOut(led_R, R);  
    fadeOut(led_G, G);  
    fadeOut(led_B, B);
    H = 255;
    W = 0;
    R = 0;
    G = 0;
    B = 0; 
  }
  
  if(input == '3'){
    Serial.println("warm white");
    fadeOut(led_H, H);
    fadeIn(led_W, 255);
    fadeOut(led_R, R);  
    fadeOut(led_G, G);  
    fadeOut(led_B, B);
    H = 0;
    W = 255;
    R = 0;
    G = 0;
    B = 0; 

  }

  if(input == '4'){
    Serial.println("Red");
    fadeOut(led_H, H);
    fadeOut(led_W, W);
    fadeIn(led_R, 255);  
    fadeOut(led_G, G);  
    fadeOut(led_B, B);
    H = 0;
    W = 0;
    R = 255;
    G = 0;
    B = 0; 

  }

  if(input == '5'){
    Serial.println("Green");
    fadeOut(led_H, H);
    fadeOut(led_W, W);
    fadeOut(led_R, R);  
    fadeIn(led_G, 255);  
    fadeOut(led_B, B);
    H = 0;
    W = 0;
    R = 0;
    G = 255;
    B = 0; 
  }

  if(input == '6'){
    Serial.println("Blue");
    fadeOut(led_H, H);
    fadeOut(led_W, W);
    fadeOut(led_R, R);  
    fadeOut(led_G, G);  
    fadeIn(led_B, 255);
    H = 0;
    W = 0;
    R = 0;
    G = 0;
    B = 255;  
  }  
  
if(input == '7'){
    Serial.println("PLAY MODE");
    digitalWrite(led_H, LOW);
    digitalWrite(led_W, LOW);
    
    while(input == '7'){
      int dtime = 2500;
      analogWrite(led_R, 50);
      delay(dtime);
      digitalWrite(led_R, LOW);
      analogWrite(led_G, 50);
      delay(dtime);
      digitalWrite(led_G, LOW);
      analogWrite(led_B, 50);
      delay(dtime);
      digitalWrite(led_B, LOW);
      analogWrite(led_R, 50);
      analogWrite(led_G, 50);
      delay(dtime);
      digitalWrite(led_R, LOW);
      analogWrite(led_B, 50);
      delay(dtime);
      digitalWrite(led_G, LOW);
      analogWrite(led_R, 50);
      delay(dtime);
      digitalWrite(led_R, LOW);
      digitalWrite(led_B, LOW);
      if(input != '7') break;
    }
    H = 0;
    W = 0;
    R = 255;
    G = 255;
    B = 255;  
  }     
}
