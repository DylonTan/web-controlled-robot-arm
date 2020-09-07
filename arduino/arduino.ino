#include <Servo.h>
#define SERVO_PIN_1 6 // Base
#define SERVO_PIN_2 9 // Limb
#define SERVO_PIN_3 10
#define SERVO_PIN_4 11

Servo servo1;
Servo servo2;
int xAxisAngle = 0;
int zAxisAngle = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  Serial.println("Arduino started.");
}

String data;

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    data = Serial.readString();
   
    if (data == "FORWARDS") {
      forwardsHandler();
    } else if (data == "LEFT") {
      leftHandler();
    } else if (data == "RIGHT") {
      rightHandler();
    } else if (data == "BACKWARDS") {
      backwardsHandler();
    }
  }
}

void forwardsHandler() {
  Serial.println("MOVING MOTOR FORWARDS");
  servo2.write(90);
}

void leftHandler() {
  Serial.println("MOVING MOTOR TO THE LEFT");
  if (xAxisAngle - 20 >= 0) {
    xAxisAngle = xAxisAngle - 20;
    servo1.write(xAxisAngle);
  }
}

void rightHandler() {
  Serial.println("MOVING MOTOR TO THE RIGHT");
  if (xAxisAngle + 20 <= 180) {
    xAxisAngle = xAxisAngle + 20;
    servo1.write(xAxisAngle);
  }
}

void backwardsHandler() {
  Serial.println("MOVING MOTOR BACKWARDS");
  servo2.write(0);
}
