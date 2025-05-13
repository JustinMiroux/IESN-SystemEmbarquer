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

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}

int16_t packetnum = 0;  // packet counter, we increment per xmission

int distance; //variable contenant distance reçue par robot
// String Buffer = "";
void loop()
{
  // if (Serial.available() > 0) {

  //   Buffer = Serial.readStringUntil('\r\n');
  //   Serial.println(Buffer);
    
  // }
  int xAxis = analogRead(A0); // Read Joysticks X-axis
  int yAxis = analogRead(A1); // Read Joysticks Y-axis

  delay(10); // Wait 1 second between transmits, could also 'sleep' here!
  //Serial.println("Transmitting..."); // Send a message to rf95_server
  
  //char radiopacket[] = "Bonjour c'est justin";
  int radiopacket[2] = {xAxis, yAxis};
  //itoa(packetnum++, radiopacket+13, 10);
  //Serial.print("Sending "); Serial.println(radiopacket[0]);
  //radiopacket[] = 0;
  
  Serial.println("Sending..."); Serial.println(xAxis); Serial.println(yAxis);
  delay(10);
  rf95.send((uint8_t *)radiopacket, 4);
  delay(10);
  rf95.waitPacketSent();


  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  //Serial.println("Waiting for reply...");
  if (rf95.waitAvailableTimeout(1000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
    distance = buf[0] + buf[1]*256;
    //Serial.println("Distance: ");
    Serial.println(distance);
    //Serial.println("cm");    
    }
    else
    {
      Serial.println("Receive failed");
    }
  } 
}
//wesh
