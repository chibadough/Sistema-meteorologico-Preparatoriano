//Hazme un favor y revisa el codigo mientas escuches:
//Super Ponybeat-Mirai Star! 
#include <MQ135.h>
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
int mq = A0;
int lect;

volatile int contadorPluv = 0;
volatile unsigned long ultimoPulso = 0;
volatile unsigned long ultimoPulsoReal = 0;

const float mmPulso = 0.3;


const int pluv = 3;
const int umbralTiempo = 300; 

float mmTotal = 0;


bool advertencia1 = false;
bool advertencia2 = false;

  #define DHTPIN 5
  #define DHTPIN1 8
  #define DHTTYPE DHT11


DHT dht(DHTPIN,DHTTYPE);
DHT dht1(DHTPIN1,DHTTYPE);

  float temp;
  float pres;

  
Adafruit_BME280 bme; 

#define PIN_MQ135 A2

MQ135 mq135_sensor(PIN_MQ135);


void setup() {
 Serial.begin(9600);
 dht.begin();
 dht1.begin();
 Wire.begin();
 bme.begin(0X76);
  pinMode(pinV,OUTPUT);
  pinMode(pinV2,OUTPUT);
  pinMode(Ane,INPUT);
  pinMode(pluv, INPUT_PULLUP);
  pinMode(mq, INPUT);

attachInterrupt(
  digitalPinToInterrupt(pluv),
  contarLluvia,
  FALLING
);
  pinMode(sensorA,INPUT);
} 
void contarLluvia()
{
  unsigned long ahora = millis();

  if (ahora - ultimoPulso > umbralTiempo)
  {
    contadorPluv++;
    ultimoPulso = ahora;
    ultimoPulsoReal = ahora;
  }
}

void loop() {
lecturA = analogRead(sensorA);
lect = analogRead(mq);


noInterrupts();
int pulsos = contadorPluv;
unsigned long ultimo = ultimoPulsoReal;
interrupts();

if (millis() - ultimo > 30000UL) 
{
  noInterrupts();
  contadorPluv = 0;
  interrupts();

  pulsos = 0;
}

mmTotal = pulsos * mmPulso;

 
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
Serial.print("Pulsos: ");
Serial.println(contadorPluv);

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
    Serial.print("lectura mq; ");

float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temp, hum1);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temp, hum1);

  Serial.print("MQ135 RZero: ");
  Serial.print(rzero);
  Serial.print("\t Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print("\t Resistance: ");
  Serial.print(resistance);
  Serial.print("\t PPM: ");
  Serial.print(ppm);
  Serial.print("\t Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm");



 delay(5000);


 }


