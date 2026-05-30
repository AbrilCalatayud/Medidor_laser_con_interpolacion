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

int tamanioTabla = 5; //modificable

float hallarContribucionAmbiente();
float obtenerTensionParaInterpolacion();
void esperarAccionDeUsuario();

void setup()
{
  Serial.begin(9600);

  pinMode(pinLaser, OUTPUT);
}

void loop()
{
  Serial.println("Comenzando calibración...");
  contribucionAmbiente = hallarContribucionAmbiente();
  Serial.println("Terminó la calibración.");

  float tensionParaInterpolar = obtenerTensionParaInterpolacion();

  //y luego interpolo con ese valor

  Serial.println("Presione una tecla para medir otra vez...");
  esperarAccionDeUsuario();
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

void esperarAccionDeUsuario()
{
  while (Serial.available() == 0)
  {
    //No hace nada, solo espera a que haya algo en el buffer del serial
  }
}