#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>




Adafruit_BMP280 bmp;

  #define DHTPIN1 2
  #define DHTPIN2 7
  #define DHTTYPE DHT11

DHT dht1(DHTPIN1,DHTTYPE);
DHT dht2(DHTPIN2,DHTTYPE); //solo para pruebas

  float temp;
  float pres;


void setup() {
 Serial.begin(9600);
 dht1.begin();
 dht2.begin(); //SOMBRA
 Wire.begin();
 bmp.begin(0x76);
}

void loop() {
  float tem1 = dht1.readTemperature();
  float hum1 = dht1.readHumidity();
  float tem2 = dht2.readTemperature(); //SOMBRA
 temp = bmp.readTemperature();
 pres = bmp.readPressure()/100;

  Serial.print("temperatura actual: ");
  Serial.print(temp);
  Serial.print("C*");
  Serial.print("pression atmosferica: ");
  Serial.print(pres);
  Serial.print("hpa");


  Serial.print("temperatura actual exterior: ");
  Serial.print(tem1);
  Serial.print("C* ");
  Serial.print("temperatura actual sombra: "); // Unicamente para pruebas.
  Serial.print(tem2);
  Serial.print("C* ");
  Serial.print(" humedad relativa: ");
  Serial.print(hum1);
  Serial.print("% ");

 delay(4000);
}
