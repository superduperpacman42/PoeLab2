#include <Servo.h>
const byte SHARP = A0;
const byte SERVO = 9;
const byte BUTTON = 8;
Servo servo;
int theta = 0;
long t0 = 0;
bool pressed = false;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO);
}

void loop() {
  if(!pressed && digitalRead(BUTTON)) {
    pressed = true;
    theta = 0;
  }
  if(pressed && millis()-t0>15) {
    float range = 1296.9/analogRead(SHARP)-2.2921;
    float x = range*sin((theta-85)*PI/180);
    float y = range*cos((theta-85)*PI/180);
    servo.write(theta%170); 
    Serial.print(theta%170-85);
    Serial.print(",");
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);
    t0 = millis();
    theta++;
    if(theta%170==0) {
      theta = 0;
      pressed = false;
    }
  }
  

}
