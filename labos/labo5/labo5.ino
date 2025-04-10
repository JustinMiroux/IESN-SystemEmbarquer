#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS  4    // "E"
#define RFM95_RST 2   // "D"
#define RFM95_INT 3   // "B"
#define RF95_FREQ 430.0

#define X A0
#define Y A1

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

int16_t packetnum = 0;  // packet counter, we increment per xmission

void loop()
{
  delay(250); // Wait 1 second between transmits, could also 'sleep' here!
  Serial.println("Transmitting..."); // Send a message to rf95_server

  unsigned int xvalue = map(analogRead(X), 0, 1023, 0, 1023);
  unsigned int yvalue = map(analogRead(Y), 0, 1023, 0, 1023);

  int data[] = {xvalue, yvalue};

  Serial.println(data[0]);
  Serial.println(data[1]);
  
  //Serial.print("Sending "); Serial.println(data[]);
  //Serial.println("Sending...");
  delay(10);
  rf95.send((uint8_t *)data, sizeof(data));

  Serial.println("Waiting for packet to complete..."); 
  delay(10);
  rf95.waitPacketSent();

  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  // Serial.println("Waiting for reply...");

  /*
  if (rf95.waitAvailableTimeout(1000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("Got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
  else
  {
    Serial.println("No reply, is there a listener around?");
  }
  */

}
