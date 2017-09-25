#include <Servo.h>
const byte SHARP = A0;
const byte SERVO_LEFT = 9;
const byte SERVO_RIGHT = 11;
const byte SERVO_CENTER = 10;
const byte BUTTON = 8;
const int R = 18;
const int RES = 5;
Servo servoLeft;
Servo servoRight;
Servo servoCenter;

int theta = 0;
int phi = 0;
long t0 = 0;
bool pressed = false;
bool clockwise = true;

void setup() {
  Serial.begin(9600);
  servoLeft.attach(SERVO_LEFT);
  servoRight.attach(SERVO_RIGHT);
  servoCenter.attach(SERVO_CENTER);
}

void loop() {
  if(!pressed && digitalRead(BUTTON)) {
    pressed = true;
    theta = 0;
    phi = 0;
  }
  if(pressed && millis()-t0>15) {
    float range = 1296.9/analogRead(SHARP)-2.2921;
    float d = R - range;
    float x, y, z;
    if(d<0 || d>R) {
      x = 0;
      y = 0;
      z = 0;
    } else if(clockwise) {
      x = d*sin((phi-85)*PI/180)*cos((170-theta)*PI/180);
      y = d*sin((phi-85)*PI/180)*sin((170-theta)*PI/180);
      z = d*cos((phi-85)*PI/180);
    } else {
      x = d*sin((phi-85)*PI/180)*cos(theta*PI/180);
      y = d*sin((phi-85)*PI/180)*sin(theta*PI/180);
      z = d*cos((phi-85)*PI/180);
    }
    Serial.print(theta*phi);
    Serial.print(",");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(z);
    t0 = millis();
    theta+=1;
    if(theta>170) {
      theta = 0;
      phi+=RES;
      clockwise = !clockwise;
      if(phi>170) {
        phi = 0;
        pressed = false;
      }
    }
    setPhi(phi);
    if(clockwise) {
      setTheta(170-theta);
    }
    else {
      setTheta(theta);
    }
  }
}

void setPhi(int ph) {
  ph = ph%171;
  servoLeft.write(ph);
  servoRight.write(170-ph);
}

void setTheta(int th) {
  th = th%171;
  servoCenter.write(th);
}
