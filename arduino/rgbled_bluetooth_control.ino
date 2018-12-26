#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 2); //arduino pin 2:rx 3:tx

int led_H = 5;  //white
int led_W = 6;  //warm white
int led_R = 9;  //red
int led_G = 10; //green
int led_B = 11; //blue

int H, W, R, G, B;

int leds[] = {5, 6, 9, 10, 11};
int brightness = 0;
int fadeAmount = 5;
int i;
bool isLF;
int previnput, input, cnt = 0;

void fadeIn(int pin, int prev, int next) {
  for (i = prev; i <= next; i++)
  {
    analogWrite(pin, i);
    delay(20);
  }
}

void fadeOut(int pin, int prev, int next) {
  for (i = prev; i >= next; i--)
  {
    analogWrite(pin, i);
    delay(20);
  }
}

void setup() {
  previnput = -1;
  input = -38;
  isLF = false;
  for (i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  Serial.println(input);
  if (BTSerial.available()) {
    previnput = (int)BTSerial.read() - 48;
    cnt++;
    if (cnt % 3 == 1) {
      if (input == -38 || input == -35 || input == 5) {
        input = previnput;
      }
      else {
        previnput = input;
      }

      Serial.println(input);
      //delay(100)
    }
  }
  if (Serial.available())
    BTSerial.write(Serial.read());

  if (input == 0) {
    Serial.println("all turn off");
    for (i = 0; i < sizeof(leds); i++) {
      analogWrite(leds[i], 0);
    }
    H = 0;
    W = 0;
    R = 0;
    G = 0;
    B = 0;
    input = -38;
  }

  else if (input == 1) {
    Serial.println("white 15");
    if (H < 15) {
      fadeIn(led_H, H, 15);
    }
    else {
      fadeOut(led_H, H, 15);
    }
    fadeOut(led_W, W, 0);
    fadeOut(led_R, R, 0);
    fadeOut(led_G, G, 0);
    fadeOut(led_B, B, 0);
    H = 15;
    W = 0;
    R = 0;
    G = 0;
    B = 0;
    input = -38;
  }

  else if (input == 2) {
    Serial.println("white 55");
    if (H < 55) {
      fadeIn(led_H, H, 55);
    }
    else {
      fadeOut(led_H, H, 55);
    }
    fadeOut(led_W, W, 0);
    fadeOut(led_R, R, 0);
    fadeOut(led_G, G, 0);
    fadeOut(led_B, B, 0);
    H = 55;
    W = 0;
    R = 0;
    G = 0;
    B = 0;
    input = -38;
  }

  else if (input == 3) {
    Serial.println("white 255");
    fadeIn(led_H, H, 255);
    fadeOut(led_W, W, 0);
    fadeOut(led_R, R, 0);
    fadeOut(led_G, G, 0);
    fadeOut(led_B, B, 0);
    H = 255;
    W = 0;
    R = 0;
    G = 0;
    B = 0;
    input = -38;
  }

  else if (input == 4) {
    Serial.println("warm white");
    if (W < 80) {
      fadeIn(led_W, W, 80);
    }
    else {
      fadeOut(led_W, W, 80);
    }
    fadeOut(led_H, H, 0);
    fadeOut(led_R, R, 0);
    fadeOut(led_G, G, 0);
    fadeOut(led_B, B, 0);
    H = 0;
    W = 80;
    R = 0;
    G = 0;
    B = 0;
    input = -38;
  } else if (input == 5) {
    Serial.println("for kids");
    digitalWrite(led_H, LOW);
    digitalWrite(led_W, LOW);

    int dtime = 250;
    analogWrite(led_R, 250);
    delay(dtime);
    digitalWrite(led_R, LOW);
    analogWrite(led_G, 250);
    delay(dtime);
    digitalWrite(led_G, LOW);
    analogWrite(led_B, 250);
    delay(dtime);
    digitalWrite(led_B, LOW);
    analogWrite(led_R, 250);
    analogWrite(led_G, 250);
    delay(dtime);
    digitalWrite(led_R, LOW);
    analogWrite(led_B, 250);
    delay(dtime);
    digitalWrite(led_G, LOW);
    analogWrite(led_R, 250);
    delay(dtime);
    digitalWrite(led_R, LOW);
    digitalWrite(led_B, LOW);

    H = 0;
    W = 0;
    R = 0;
    G = 0;
    B = 0;
    //input = 5;
  }
}
