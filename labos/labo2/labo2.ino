#define PIN 11

float CONTROL = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0) {
    CONTROL = (Serial.read() * 2.55);
    Serial.flush();
  }
  if (Serial.read() != 10) {
    analogWrite(PIN, CONTROL);
  }
  Serial.println(CONTROL);
  delay(1000);
  
}
