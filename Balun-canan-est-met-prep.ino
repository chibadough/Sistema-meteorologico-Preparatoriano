//Hazme un favor y revisa el codigo mientas escuches:
//Super Ponybeat-Mirai Star! 
#include <Adafruit_BME280.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>
int pinV =7;
int pinV2 =4;
int Ane = A3;
int l1;
float volt;
float vel;
int sensorA = A2;
float lecturA;


const float mmPulso = 0.3;
float mmTotal = 0;
int pluv = 3;
int lectura;
int estadoPost = 0; 


bool advertencia1 = false;
bool advertencia2 = false;

  #define DHTPIN 5
  #define DHTPIN1 8
  #define DHTTYPE DHT11


DHT dht(DHTPIN,DHTTYPE);
DHT dht1(DHTPIN1,DHTTYPE);

  float temp;
  float pres;

  
Adafruit_BME280 bme; // use I2C interface


void setup() {
 Serial.begin(9600);
 dht.begin();
 dht1.begin();
 Wire.begin();
 bme.begin();
  pinMode(pinV,OUTPUT);
  pinMode(pinV2,OUTPUT);
  pinMode(Ane,INPUT);
  pinMode(pluv,INPUT_PULLUP);
  pinMode(sensorA,INPUT);
}

void loop() {
lectura = digitalRead(3);
lecturA = analogRead(sensorA);

if(lectura == HIGH && estadoPost == LOW){
  mmTotal += mmPulso;
}


 
float tem1 = dht.readTemperature();
float hum1 = dht.readHumidity();
 temp = bme.readTemperature();
 pres = bme.readPressure() /100;

 l1 = analogRead(Ane);
 volt = l1*(5000.0/1023.0); //voltaje (mv) obtenido del anemometro
 vel = 0.34 * volt; // funcion f(x) = 0.34(x) correspondiente al anemometro

 

 if((isnan(tem1) || isnan(hum1))&& advertencia1 == false){
 advertencia1 = true;
 Serial.println("Reinciando EL dht11");
 digitalWrite(pinV, LOW);
 delay(2000);
 digitalWrite(pinV, HIGH);
 delay(2000);
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
 digitalWrite(pinV2, HIGH);
 }

 if (isnan(temp) || isnan(pres)){
  Serial.println("ERROR CON EL BME280: REVISAR PUESTO QUE NO HAY REPUESTO");
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
   Serial.print("Precipitacion: ");
  Serial.print(mmTotal);
  Serial.println("mm");
  Serial.println("");


if (lecturA >= 200){
  Serial.println("===ESTA EMPEZANDO A LLOVER===");
} else if(lecturA >= 600){
  Serial.println("===DEFINITAVEMENTE ESTA LLOVIENDO===");
} else if (lecturA == 0 && mmTotal >= 0.66){
  Serial.println("===REVISAR EL SENSOR DE LLUVIA O POSIBLE MOVIMIENTO EN FALSO DEL BALANCIN DEL PLUVIOMETRO===");
}


  Serial.println("=====Temperatura en sombra y humedad relativa====");
  Serial.print("temperatura actual exterior: ");
  Serial.print(tem1);
  Serial.println("C* ");
  Serial.print(" humedad relativa: ");
  Serial.print(hum1);
  Serial.println("% ");
    Serial.println("");


 delay(5000);

estadoPost = lectura;
 }

