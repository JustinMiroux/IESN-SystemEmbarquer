#include <SPI.h>
#include <RH_RF95.h>
#include <NewPing.h>

#define RFM95_RST     A2   // "A"
#define RFM95_CS      4   // "B"
#define RFM95_INT     3    // "C"

#define RF95_FREQ 430.0
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Moteur 1 (Gauche) :
#define enA 10
#define in1 9
#define in2 8

// Moteur 2 (Droite) :
#define enB 5
#define in4 6
#define in3 7

int motorSpeedA = 0;
int motorSpeedB = 0;

#define TRIGGER_PIN A1    //bleu
#define ECHO_PIN 2        //vert
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);

  while (!Serial) {
    delay(1);
  }

  delay(100);
  Serial.println("Feather LoRa RX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }

  Serial.println("LoRa radio init Success");

  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }

  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  rf95.setTxPower(23, false);
}

int xAxis = 512;
int yAxis = 512;
int mode = 0;
int distance;

void loop() {

  //sonar
  int uS = sonar.ping();
  distance = uS / US_ROUNDTRIP_CM;
  delay(10);

  if (rf95.available())
  {

    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t  len = sizeof(buf);

    //attend et lis données du joystick envoié via Lora
    if (rf95.recv(buf, &len))
    {
      xAxis = buf[0] + buf[1]*256;
      yAxis = buf[2] + buf[3]*256;
      mode = buf[4] + buf[5]*256;
      // Serial.print("Mode : ");
      // Serial.println(mode);

      //envoi de la distance
      int packet[1];
      packet[0] = distance;
      Serial.println(distance);
      rf95.send((uint8_t*)packet,sizeof(packet));
      rf95.waitPacketSent();
    }

    else
    {
      Serial.println("Message receiving failed");
    }

  }

  if (mode == 1)
  {
    if (distance < 40)
    {
      delay(100);
      yAxis = 960;
      xAxis = 512;
      delay(100);
      yAxis = 512;
      xAxis = 960;
      delay(10);
    }
    else
    {
      yAxis = 64;
      xAxis = 512;
    }
  }
    // Serial.print("Valeur x: ");
    // Serial.println(xAxis);
    // Serial.print("Valeur y: ");
    // Serial.println(yAxis);
  
  // Y-axis used for forward and backward control
  if (yAxis < 470) {
    //Serial.println("boucle y < 470");
    // Set Motor A backward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }
  else if (yAxis > 550) {
    //Serial.println("boucle y > 550");
    // Set Motor A forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  // X-axis used for left and right control
  if (xAxis < 470) {
    //Serial.println("boucle x < 470");
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 470, 0, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }
  }
  if (xAxis > 550) {
    //Serial.println("boucle x > 550");
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B

  
}