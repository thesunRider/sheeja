#include <SPI.h>
#include "WiFi.h"

#define LENGTH_MSG 2*3000
#include "AsyncUDP.h"

const char *ssid = "iobeam";
const char *password = "12345678";
uint8_t msg_send[LENGTH_MSG];

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

  SPISettings spiSettings(1800000,  //  1 MHz (1us) clock
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
  udp.listen(1234);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0;i<LENGTH_MSG-1;i+=2){
    digitalWrite(_csPin, LOW);  //  pull CS low
    //  read 2 bytes ADC value
    byte readingH = SPI.transfer(0);
    byte readingL = SPI.transfer(0);
    digitalWrite(_csPin, HIGH);  //  de-assert CS
    uint16_t reading = ((readingH & 0b00011111) << 7) +  ((readingL & 0b11111110) >> 1); 
    msg_send[i] =  (uint8_t) (((uint16_t)reading) & 0xFF);
    msg_send[i+1] = (uint8_t) (((uint16_t)reading >> 8) & 0xFF);
  }
  
  //  combine 2 bytes ADC value into uint16_t
  udp.broadcast(msg_send,LENGTH_MSG);

}
