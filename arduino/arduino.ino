void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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
}

void leftHandler() {
  Serial.println("MOVING MOTOR TO THE LEFT");
}

void rightHandler() {
  Serial.println("MOVING MOTOR TO THE RIGHT");
}

void backwardsHandler() {
  Serial.println("MOVING MOTOR BACKWARDS");
}
