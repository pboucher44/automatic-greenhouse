#include <Servo.h>
#include "DHT.h"

Servo monservo;
int relayEau = 10;
int currentState;
const int buttonBroche = 11;
const int buttonBrocheEau = 7;
int etatButton;
int etatButtonEau;
int cervomoteur = 12;
int lumiere = 8;
bool initTour = true;
int valLumiere;
int valHumidityTerre;
int chaleur = 13;

#define DHTPIN 3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  pinMode(relayEau, OUTPUT);
  digitalWrite(relayEau, LOW);
  pinMode(lumiere, OUTPUT);
  digitalWrite(lumiere, LOW);
  pinMode(chaleur, OUTPUT);
  digitalWrite(chaleur, LOW);
  pinMode(buttonBroche, INPUT);
  pinMode(buttonBrocheEau, INPUT);

  dht.begin();

  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps

  monservo.attach(12);
  monservo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  etatButton = digitalRead(buttonBroche);
  etatButtonEau = digitalRead(buttonBrocheEau);

  valLumiere=analogRead(0);   //connect grayscale sensor to Analog 0

  delay(100);

  if(valLumiere < 500){
    digitalWrite(lumiere, HIGH);
  } else {
    digitalWrite(lumiere, LOW);
  }     

  valHumidityTerre = analogRead(8);
  if( valHumidityTerre > 500 || etatButtonEau  == HIGH) {
    digitalWrite(relayEau, HIGH);
  } else {
    digitalWrite(relayEau, LOW);
  }

    // read humidity
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  tempC = tempC*10;

  Serial.print("humi : ");
  Serial.println(humi);

  Serial.print("temp : ");
  Serial.println(tempC);
  
  if(tempC < 12) {
      digitalWrite(chaleur, HIGH);
  } else {
      digitalWrite(chaleur, LOW);
  }

  if(humi > 20 || etatButton  == HIGH) {
    monservo.write(180);
  }else{
    monservo.write(0);
  }
  
}
