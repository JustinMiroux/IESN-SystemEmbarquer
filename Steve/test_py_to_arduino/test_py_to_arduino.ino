void setup() {

  Serial.begin(115200);

}

String Buffer = "";

void loop() {

  if (Serial.available() > 0) {
    Buffer = Serial.readStringUntil('\r\n');

    if (Buffer == "auto") {
      Serial.println("auto reçu");
    }

    else if (Buffer == "manual") {
      Serial.println("manual reçu");
    }

    else {
      Serial.println("Autre chose reçu");
    }
  }

}
