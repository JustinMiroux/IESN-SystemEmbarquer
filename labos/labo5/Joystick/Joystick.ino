#define X A1
#define Y A2

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned int xvalue = map(analogRead(X), 0, 1023, 0, 255);
  unsigned int yvalue = map(analogRead(Y), 0, 1023, 0, 255);
  Serial.println(xvalue);
  Serial.println(yvalue);
}