#include <Arduino.h>

//cambiar cuando sepa a qué pines los voy a conectar
const int pinTransistor = A0;
const int pinLaser = A1;

float contribucionAmbiente = 0;

struct ParTensionDistancia
{
  float tension;
  int distancia;
};

ParTensionDistancia tabla[] = {
  //modificar cuando se tengan los valores reales
  {1.5, 50},
  {2.0, 40},
  {3.0, 30},
  {4.0, 20},
  {4.5, 10}
};

float hallarContribucionAmbiente();
float obtenerTensionParaInterpolacion();
void recalibrarSiSeMovio();

void setup()
{
  Serial.begin(9600);

  pinMode(pinLaser, OUTPUT);
  
  Serial.println("Comenzando calibración... Se busca la contribución de la luz del ambiente...");
  contribucionAmbiente = hallarContribucionAmbiente();
  Serial.println("Terminó la calibración.");
}

void loop()
{
  float tensionParaInterpolar = obtenerTensionParaInterpolacion();

  //y luego interpolo con ese valor
  
  recalibrarSiSeMovio();
}

float hallarContribucionAmbiente()
{
  digitalWrite(pinLaser, LOW);

  float tensionSinLaser = analogRead(pinTransistor);

  digitalWrite(pinLaser, HIGH);

  float tensionConLaser = analogRead(pinTransistor);

  return (tensionConLaser - tensionSinLaser);
}

float obtenerTensionParaInterpolacion()
{
  float tensionEnBruto = analogRead(pinTransistor);

  return (tensionEnBruto - contribucionAmbiente);
}

void recalibrarSiSeMovio()
{
  Serial.println("¿El sistema medidor sigue exactamente en el mismo lugar?");
  Serial.println("Tocar S si es así, sino otra tecla.");
  String entradaSerial = Serial.readString();

  if(entradaSerial == "S" || entradaSerial == "s")
  {
    Serial.println("Comenzando recalibración...");
    contribucionAmbiente = hallarContribucionAmbiente();
    Serial.println("Terminó la recalibración.");
  }
}