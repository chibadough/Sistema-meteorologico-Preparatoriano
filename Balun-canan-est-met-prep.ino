#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>
int pinV =7;
int pinV2 =4;
int Ane = A3;
int l1;
float volt;
float vel;


Adafruit_BMP280 bmp;

bool advertencia1 = false;
bool advertencia2 = false;

  #define DHTPIN 5
  #define DHTPIN1 8
  #define DHTTYPE DHT11


DHT dht(DHTPIN,DHTTYPE);
DHT dht1(DHTPIN1,DHTTYPE);

  float temp;
  float pres;


void setup() {
 Serial.begin(9600);
 dht.begin();
 dht1.begin();
 Wire.begin();
 bmp.begin(0x76);
  pinMode(pinV,OUTPUT);
  pinMode(pinV2,OUTPUT);
  pinMode(Ane,INPUT);
}

void loop() {
  float tem1 = dht.readTemperature();
  float hum1 = dht.readHumidity();
 temp = bmp.readTemperature();
 pres = bmp.readPressure()/100;
 l1 = analogRead(Ane);
 volt = l1*(5000.0/1023.0); //voltaje (mv) obtenido del anemometro
 vel = 0.34 * volt; // funcion f(x) = 3.4(x) correspondiente al anemometro

 

 if((isnan(tem1) || isnan(hum1))&& advertencia1 == false){
 advertencia1 = true;
 Serial.println("Reinciando EL dht11");
 digitalWrite(pinV, LOW);
 delay(1000);
 digitalWrite(pinV, HIGH);
 delay(1000);
  tem1 = dht.readTemperature();
  hum1 = dht.readHumidity();
 } else if ((isnan(tem1) || isnan(hum1)) && advertencia1 == true && advertencia2 == false){
   Serial.println("Cambiando a dht11 de repuesto");
   advertencia2 = true;
   digitalWrite(pinV2, HIGH);
   tem1 = dht1.readTemperature();
   hum1 = dht1.readHumidity();
 } else if ((isnan(tem1) || isnan(hum1)) && advertencia2 == true){
 Serial.println("PROBLEMA CON EL DHT11: REVISAR");
 } else {
 digitalWrite(pinV, HIGH);
 digitalWrite(pinV2, LOW);
 }

 if (isnan(temp) || isnan(pres)){
  Serial.println("ERROR CON EL BMP280: REVISAR PUESTO QUE NO HAY REPUESTO");
 }

 


  
  Serial.println("=====Datos generales=====");
  Serial.print("temperatura actual: ");
  Serial.print(temp);
  Serial.println("C*");
  Serial.print("presion atmosferica: ");
  Serial.print(pres);
  Serial.println("hpa");
   Serial.print("Velocidad del viento: ");
  Serial.print(vel);
  Serial.println("Km/h");
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

