#include <SPI.h>
#include "WiFi.h"
#include "AsyncUDP.h"

const char *ssid = "iobeam";
const char *password = "12345678";

/*
------Connections----------
MISO: 19
SCK: 18
SS: 5
*/
#define _csPin 5
AsyncUDP udp;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting");
  pinMode(_csPin, OUTPUT);

  SPISettings spiSettings(10000000,  //  1 MHz (1us) clock
                          MSBFIRST,         //  MSB shifted first
                          SPI_MODE0);       //  SPI Mode 0,0

  SPI.begin();                        //  initialize the SPI bus
                                      //  sets SCK, POCI, CS to output
                                      //  pulls SCK, PICO low, CS high
  SPI.beginTransaction(spiSettings);  //  "lock" the SPI bus for
                                      //  own exclusive usage
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while (1) {
      delay(1000);
    }
  }
  Serial.println(WiFi.localIP());
  if (udp.listen(1234)) {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length());
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
      //reply to the client
      packet.printf("Got %u bytes of data", packet.length());
    });
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(_csPin, LOW);  //  pull CS low
  //  read 2 bytes ADC value
  byte readingH = SPI.transfer(0);
  byte readingL = SPI.transfer(0);
  digitalWrite(_csPin, HIGH);  //  de-assert CS
 // uint16_t reading = ((readingH & 0b00011111) << 7) +  //  data in LSB 5 bits
 //                    ((readingL & 0b11111110) >> 1); 
  uint8_t msg_send[] = {(readingH & 0b00011111) << 7,(readingL & 0b11111110) >> 1};

  //  combine 2 bytes ADC value into uint16_t
  udp.broadcast(msg_send,2);

}
