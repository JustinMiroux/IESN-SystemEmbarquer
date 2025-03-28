#include <LiquidCrystal.h>
#define READ A1

const int rs = 2, en = 4, data1 = 5, data2 = 6, data3 = 7, data4 = 8;
LiquidCrystal lcd(rs, en, data1, data2, data3, data4);

void setup() {
  // put your setup code here, to run once:
  pinMode(READ, INPUT);
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float value = analogRead(READ);
  float convvalue = value / 1023;
  float voltvalue = convvalue * 5;
  float celcius = voltvalue * 100 - 273;
  lcd.print(celcius);
  Serial.println(celcius);
  delay(1000);
  lcd.setCursor(0, 0);
}
