#include <Arduino.h>
#include <DHTesp.h>
#include <TFT_eSPI.h>

DHTesp          dht;
int             interval = 2000;
unsigned long   lastDHTReadMillis = 0;
float           humidity = 0;
float           temperature = 0;
char            buf[50];

#define         DHTPIN 18

TFT_eSPI tft = TFT_eSPI();

void readDHT22() {
    unsigned long currentMillis = millis();

    if(millis() > lastDHTReadMillis + interval) {
        lastDHTReadMillis = currentMillis;

        humidity = dht.getHumidity();
        temperature = dht.getTemperature();
    }
}

void setup() {
    Serial.begin(115200); 
    dht.setup(DHTPIN, DHTesp::DHT22);   // Connect DHT Sensr to GPIO 18
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Atmosphere Meter", 60, 20, 4);
    delay(1000);
    Serial.println();
    Serial.println("Humidity (%)\tTemperature (C)");
} 

void loop() {
    readDHT22();

    sprintf(buf, "%.1f%%     %.1f°C", humidity, temperature);
    tft.fillRect(80, 60, 180, 23, TFT_BLACK);
    tft.drawString(buf, 90, 60, 4);
    Serial.printf("%.1f\t%.1f\n", humidity, temperature);
    delay(2000);
}
