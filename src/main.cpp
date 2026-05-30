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
bool comprobarValorEstaDentroDelRango(float);
float interpolar(float);
void limpiarBuffer();
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

  if(comprobarValorEstaDentroDelRango(tensionParaInterpolar))
  {
    float distanciaCalculada = interpolar(tensionParaInterpolar);

    Serial.print("Tensión medida: ");
    Serial.println(tensionParaInterpolar);
    Serial.print("Distancia caluclada: ");
    Serial.println(distanciaCalculada);
  }

  limpiarBuffer();
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

bool comprobarValorEstaDentroDelRango(float tension)
{
  if(tension < tabla[0].tension || tension > tabla[tamanioTabla-1].tension)
  {
    Serial.println("La distancia está fuera del rango previsto. Mueva el sistema o el objeto.");
    return false;
  }

  return true;
}

float interpolar(float tension)
{
  for (int i = 0; i < tamanioTabla - 1; i++)
  {
    if (tension >= tabla[i].tension && tension <= tabla[i+1].tension)
    {

      float x0 = tabla[i].tension;
      float y0 = tabla[i].distancia;
      float x1 = tabla[i+1].tension;
      float y1 = tabla[i+1].distancia;

      return y0 + (tension - x0) * (y1 - y0) / (x1 - x0);
    }
  }
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