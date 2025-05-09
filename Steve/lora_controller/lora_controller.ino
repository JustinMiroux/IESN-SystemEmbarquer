#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS  4    // "E"
#define RFM95_RST 2   // "D"
#define RFM95_INT 3   // "B"

#define RF95_FREQ 430.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() 
{
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);

  while (!Serial) {
    delay(1);
  }

  delay(100);
  Serial.println("Feather LoRa TX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }

  Serial.println("LoRa radio init OK!");

  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }

  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  rf95.setTxPower(23, false);

}

int16_t packetnum = 0;

int distance;
String Buffer = "";
int mode = 0;

void loop()
{
  if (Serial.available() > 0) {

    Buffer = Serial.readStringUntil('\n');
    Serial.flush();
    Buffer = Buffer.substring(0,4);
    
  }
  int xAxis = analogRead(A0); // Read Joysticks X-axis
  int yAxis = analogRead(A1); // Read Joysticks Y-axis
  
  if (Buffer == "auto") {
    mode = 1;
  }

  else if (Buffer == "manu") {
    mode = 0;
  }

  delay(10);
  int radiopacket[5] = {xAxis, yAxis, mode};
  
  delay(10);
  rf95.send((uint8_t *)radiopacket, 6);
  delay(10);
  rf95.waitPacketSent();
  delay(10);

  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf95.available() > 0)
  { 

    if (rf95.recv(buf, &len))
    {
    
      distance = buf[0] + buf[1]*256;
    
    }

    else
    {
      Serial.println("Receive failed");
    }
    
  }
  else{
    Serial.println("Test available");
  }

  Serial.println(distance);
  
}
