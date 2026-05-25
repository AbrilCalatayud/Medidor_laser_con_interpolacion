#include <Arduino.h>

//cambiar cuando sepa a qué pines los voy a conectar
const int pinTransistor = A0;
const int pinLaser = A1;

int contribucionAmbiente = 0;

void setup() {
  int tensionSinLaser = analogRead(pinTransistor);

  pinMode(pinLaser, OUTPUT);
  digitalWrite(pinLaser, HIGH);

  int tensionConLaser = analogRead(pinTransistor);

  contribucionAmbiente = tensionConLaser - tensionSinLaser;
}

void loop() {
}