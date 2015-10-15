#include "DHT.h"
 
#define DHTPIN A3 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

//Códigos implementados:
// 1) Orvalho
// 2) Umidade da Terra
// 3) Torneira
// Leônidas


//dht_dpin DHT11; //Inicializa o sensor


int sensUmidade;
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum
int saida_torneira = 4; // PINO 04 DIGITAL            
#define dht_dpin A3 //Pino DATA do Sensor ligado na porta Analogica A1

 
void setup()
{
  Serial.begin(9600);
  Serial.println("Projeto Arduino - IRRIGACAO");
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(saida_torneira, OUTPUT);    
  Serial.println("DHTxx test!");
  dht.begin();  
}
//Loop Principal Sensor Umidade
void loop()
{
   int sensUmidade = analogRead(A1);
   int senOrvalho = analogRead(A0);
   int Porcento = map(sensUmidade, 1023, 0, 0, 100);
   int range = map(senOrvalho, sensorMin, sensorMax, 0, 3);
   double porcent_orvalho = map(senOrvalho, sensorMin, sensorMax, 100, 0);
   
  
  //Serial.print("Valor%: ");
  //Serial.println(porcent_orvalho);
  Serial.println("_______________________________________________________________________________________________");
  
  // range value:
  switch (range) {
 case 0:    // Sensor getting wet
    Serial.println("GRANDE VOLUME DE CHUVA");
    break;
 case 1:    // Sensor getting wet
    Serial.println("CHOVENDO!!");
    break;
 case 2:    // Sensor dry - To shut this up delete the " Serial.println("Not Raining"); " below.
    Serial.println("NAO ESTA CHOVENDO...MANDE CHUVA DEUS!!");
    break;
  }
    
  Serial.print("% Orvalho: ");
  //Serial.println("%");
  Serial.println(porcent_orvalho); 
   
  if(Porcento <=40 && porcent_orvalho <= 40) 
  { Serial.print("% Umidade: ");
    Serial.println(Porcento);
    Serial.println("IRRIGANDO...");
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(saida_torneira, HIGH);
    //digitalWrite(saida_torneira, LOW);
  }
  else 
  { Serial.print("% Umidade: ");
    Serial.println(Porcento);
    Serial.println("UMIDADE ESTA OK!!...");
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    digitalWrite(saida_torneira, LOW);
    //digitalWrite(saida_torneira, HIGH);
  }
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else
  {
    Serial.print("Umidade: ");
    Serial.print(h,2);
    Serial.print("%   ");
    Serial.print("Temperatura: ");
    Serial.print(t,2);
    Serial.println(" *C");
  }

  //
  delay(1000);
}

