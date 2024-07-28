#include <WiFi.h>
#include <WiFiMulti.h>

byte i = 0;

byte serialBuffer[2048];
int serialBufferLength = 0; //not creating a ring buffer. The buffer should be large enough to never overflow
uint32_t lastFlushMicros = 0;

WiFiServer wifiServer(23); //Register as a telnet server
WiFiUDP wifiUDPServer;
IPAddress broadcastAddr(192,168,4,255);

void setup()
{
    delay(5000); //just for testing. Don't use in production

    Serial.begin(115200);

    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP32DUE", "1234PASSWORD");

    Serial.print("Wifi setup as SSID ");
    Serial.println("ESP32DUE");
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    Serial.print("Done with init\n");
}

void loop()
{
    serialBufferLength = 400;
    //If the max time has passed or the buffer is almost filled then send a frame out
    if ((micros() - lastFlushMicros > 500000) ) {
        //Serial.write('*');
        wifiUDPServer.begin(17222);
        wifiUDPServer.beginPacket(broadcastAddr, 17222);
        wifiUDPServer.write(serialBuffer, serialBufferLength);
        wifiUDPServer.endPacket();
        wifiUDPServer.stop();
        lastFlushMicros = micros();
    }
}