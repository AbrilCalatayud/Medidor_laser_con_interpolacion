#include <Arduino.h>

//cambiar cuando sepa a qué pines los voy a conectar
const int pinTransistor = A0;
const int pinLaser = A1;

int contribucionAmbiente = 0;

struct ParTensionDistancia
{
  int tension;
  int distancia;
};

ParTensionDistancia tabla[] = {
  //modificar cuando se tengan los valores reales
  {100, 50},
  {200, 40},
  {300, 30},
  {400, 20},
  {500, 10}
};

int hallarContribucionAmbiente();
int obtenerTensionParaInterpolacion();

void setup()
{
  Serial.begin(9600);

  pinMode(pinLaser, OUTPUT);
  
  Serial.println("Comenzando calibración. Se busca la contribución de la luz del ambiente.");
  contribucionAmbiente = hallarContribucionAmbiente();
  Serial.println("Terminó la calibración.");
}

void loop()
{
  int tensionParaInterpolar = obtenerTensionParaInterpolacion();

  //y luego interpolo con ese valor
}

int hallarContribucionAmbiente()
{
  int tensionSinLaser = analogRead(pinTransistor);

  digitalWrite(pinLaser, HIGH);

  int tensionConLaser = analogRead(pinTransistor);

  return (tensionConLaser - tensionSinLaser);
}

int obtenerTensionParaInterpolacion()
{
  int tensionEnBruto = analogRead(pinTransistor);

  return (tensionEnBruto - contribucionAmbiente);
}