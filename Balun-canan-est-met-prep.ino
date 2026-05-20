#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>
int pinV =7;


Adafruit_BMP280 bmp;

  #define DHTPIN 5
  #define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

  float temp;
  float pres;


void setup() {
 Serial.begin(9600);
 dht.begin();
 Wire.begin();
 bmp.begin(0x76);
  pinMode(pinV,OUTPUT);
}

void loop() {
  float tem1 = dht.readTemperature();
  float hum1 = dht.readHumidity();
 temp = bmp.readTemperature();
 pres = bmp.readPressure()/100;

 if(isnan(tem1) || isnan(hum1)){
 Serial.print("Reinciando EL dht11");
 digitalWrite(pinV,LOW);
 delay(1000);
 digitalWrite(pinV,HIGH);
 } else{
 digitalWrite(pinV,HIGH);
 }
  
  Serial.println("=====Datos generales=====");
  Serial.print("temperatura actual: ");
  Serial.print(temp);
  Serial.println("C*");
  Serial.print("presion atmosferica: ");
  Serial.print(pres);
  Serial.println("hpa");
  Serial.println("");

  Serial.println("=====Temperatura en sombra y humedad relativa====");
  Serial.print("temperatura actual exterior: ");
  Serial.print(tem1);
  Serial.println("C* ");
  Serial.print(" humedad relativa: ");
  Serial.print(hum1);
  Serial.println("% ");
    Serial.println("");


 delay(4000);

 }
