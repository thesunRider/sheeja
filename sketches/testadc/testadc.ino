#include <SPI.h>

/*
MOSI: 23
MISO: 19
SCK: 18
SS: 5
*/
#define _csPin 5

uint16_t readADC() {
  //  SPI settings for MCP3201 as per its datasheet

  digitalWrite(_csPin, LOW);  //  pull CS low

  //  read 2 bytes ADC value
  byte readingH = SPI.transfer(0);
  byte readingL = SPI.transfer(0);

  digitalWrite(_csPin, HIGH);  //  de-assert CS

  //  combine 2 bytes ADC value into uint16_t
  uint16_t reading = ((readingH & 0b00011111) << 7) +  //  data in LSB 5 bits
                     ((readingL & 0b11111110) >> 1);   //  data in MSB 7 bits

  return reading;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting");
  pinMode(_csPin, OUTPUT);

  SPISettings spiSettings(SPI_CLOCK_DIV16,  //  1 MHz (1us) clock
                          MSBFIRST,         //  MSB shifted first
                          SPI_MODE0);       //  SPI Mode 0,0

  SPI.begin();                        //  initialize the SPI bus
                                      //  sets SCK, POCI, CS to output
                                      //  pulls SCK, PICO low, CS high
  SPI.beginTransaction(spiSettings);  //  "lock" the SPI bus for
                                      //  own exclusive usage
  //SPI.begin();
  //SPI.beginTransaction(SPISettings(1500000, MSBFIRST, SPI_MODE0));  //1mhz clock
}

void loop() {
  // put your main code here, to run repeatedly:
  readADC();
  //delay(1000);
}
