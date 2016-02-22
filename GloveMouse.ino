#include <Wire.h>
#include <Mouse.h>
#include <ADXL345.h>

const float alpha = 0.5;

double fXg = 0;
double fYg = 0;
double fZg = 0;
ADXL345 acc;

#define LBUT  0
#define RBUT  1


void setup()
{
  acc.begin();
  Wire.begin();                
  Serial.begin(9600);    
  delay(100);

  pinMode(LBUT, INPUT);
  digitalWrite(LBUT, HIGH);
  pinMode(RBUT, INPUT);
  digitalWrite(RBUT, HIGH);
}


void loop()
{
  double Xg, Yg, Zg;
  acc.read(&Xg, &Yg, &Zg);
  int vx = map(Xg, -16000, 16000, 90, -90);
  int vy = map(Yg, -16000, 16000, 90, -90);
  Mouse.move(angleToDistance(vx), angleToDistance(vy));
  if (digitalRead(LBUT) == HIGH) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
  if (digitalRead(RBUT) == HIGH) {
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }
  delay(20);
}

int angleToDistance(int a) {
  if (a < -80) {
    return -40;
  }
  else if (a < -65) {
    return -20;
  }
  else if (a < -50) {
    return -10;
  }
  else if (a < -15) {
    return -5;
  }
  else if (a < -5) {
    return -1;
  }
  else if (a > 80) {
    return 40;
  }
  else if (a > 65) {
    return 20;
  }
  else if (a > 15) {
    return 10;
  }
  else if (a > 5) {
    return 1;
  }
  else {
    return 0;
  }
}

