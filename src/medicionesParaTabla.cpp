#include <Arduino.h>

//cambiar cuando sepa a qué pines los voy a conectar
const int pinFototransistor = A0;
const int pinLaser = A1;

float contribucionAmbiente = 0;

float hallarContribucionAmbiente();
float obtenerTensionParaTabla();
void limpiarBuffer();
void esperarAccionDeUsuario();

void setup()
{
  Serial.begin(9600);

  pinMode(pinFototransistor, INPUT);

  pinMode(pinLaser, OUTPUT);
}

void loop()
{
  Serial.println("Comenzando calibración...");
  contribucionAmbiente = hallarContribucionAmbiente();
  Serial.println("Terminó la calibración.");

  float tensionParaInterpolar = obtenerTensionParaTabla();

  Serial.print("Tensión: ");
  Serial.println(tensionParaInterpolar);

  limpiarBuffer();
  Serial.println("Presione una tecla para medir otra vez...");
  esperarAccionDeUsuario();
}

float hallarContribucionAmbiente()
{
  digitalWrite(pinLaser, LOW);

  float tensionSinLaser = analogRead(pinFototransistor);

  digitalWrite(pinLaser, HIGH);

  float tensionConLaser = analogRead(pinFototransistor);

  return (tensionConLaser - tensionSinLaser);
}

float obtenerTensionParaTabla()
{
  float tensionEnBruto = analogRead(pinFototransistor);

  return (tensionEnBruto - contribucionAmbiente);
}

void limpiarBuffer()
{
  while(Serial.available() > 0)
  {
    Serial.read(); // consume caracter por caracter y deja el buffer sin nada al terminar
  }
}

void esperarAccionDeUsuario()
{
  while(Serial.available() == 0)
  {
    //No hace nada, solo espera a que haya algo en el buffer del serial
  }
}