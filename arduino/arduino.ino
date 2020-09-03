#include <Servo.h>
#define SERVO_PIN_1 6 // Base
#define SERVO_PIN_2 9
#define SERVO_PIN_3 10
#define SERVO_PIN_4 11

Servo servo1;
Servo servo2;
int angle = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
}

String data;

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
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
  if (angle + 20 <= 180) {
    angle = angle + 20;
    servo2.write(angle);
  }
}

void leftHandler() {
  Serial.println("MOVING MOTOR TO THE LEFT");
  if (angle - 20 <= 180) {
    angle = angle - 20;
    servo1.write(angle);
  }
}

void rightHandler() {
  Serial.println("MOVING MOTOR TO THE RIGHT");
  if (angle + 20 <= 180) {
    angle = angle + 20;
    servo1.write(angle);
  }
}

void backwardsHandler() {
  Serial.println("MOVING MOTOR BACKWARDS");
  if (angle - 20 <= 180) {
    angle = angle - 20;  
    servo2.write(angle);
  }
}
