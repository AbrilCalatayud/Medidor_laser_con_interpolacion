#include <Arduino.h>

//cambiar cuando sepa a qué pines los voy a conectar
const int pinTransistor = A0;
const int pinLaser = A1;

int contribucionAmbiente = 0;

int hallarContribucionAmbiente();

void setup() {
  pinMode(pinLaser, OUTPUT);
  
  contribucionAmbiente = hallarContribucionAmbiente();
}

void loop() {
}

int hallarContribucionAmbiente() {
  int tensionSinLaser = analogRead(pinTransistor);

  digitalWrite(pinLaser, HIGH);

  int tensionConLaser = analogRead(pinTransistor);

  return (tensionConLaser - tensionSinLaser);
}