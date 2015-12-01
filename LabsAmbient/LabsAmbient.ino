#include <Phant.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>

//AREF en 3.3
#define aref_voltage 3.3         

//Pin de datos de DHT22/AM2302
#define DHTPIN 2
DHT dht(DHTPIN, DHT22);  // Tipo de DHT conectado

//Pin del sensor de luz
int lightPin = 0;       //ANALOG0

//Pin del sensor de temperatura TMP36 
int tempPin = 1;        //ANALOG1

//Ethernet
EthernetClient client;
bool isConnected = false;                         //Si se conectó en el setup
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
unsigned long lastConnectionTime = 0;             //Ultima conexión
const unsigned long postingInterval = 5L * 1000L; //Intervalo en envío cada 5 segundos
char buffer[200], buff1[6], buff2[6];             //Buffers para armar los strings

const char *server="labsambient.azurewebsites.net";

void send_request(float temp, float hum, int light)
{
  Serial.println("POST: Preparing");
  
  if (client.connect(server, 80)) {
  
    // POST URI
    sprintf(buffer, "POST %s HTTP/1.1", "/");
    client.println(buffer);

    // Host header
    sprintf(buffer, "Host: %s", server);
    client.println(buffer);
     
    // Content-Type
    client.println("Content-Type: application/atom+xml;type=entry;charset=utf-8");

    //Arma strings con los valores de temperatura y humedad
    dtostrf(temp, 5, 2, buff1);
    dtostrf(hum, 5, 2, buff2);

    //Arma el body en JSON, para calcular el tamaño
    sprintf(buffer, "{\"Temperature\": %s, \"Humidity\": %s, \"Light\": %d }", buff1, buff2, light);

    // Content-Length (con el tamaño del body)
    client.print("Content-Length: ");
    client.println(strlen(buffer));
    
    //Fin de los headers
    client.println();
    
    //Evía el body
    client.println(buffer);

    Serial.println("POST: Sent");
  } else {
    Serial.println("POST: Failed");
  }
}

void wait_response()
{
  //Mientras no haya resultado y no se haya desconectado
  while (!client.available()) {
    if (!client.connected()) {
      //Si no está desconectado sale.
      return;
    }
  }

  //Mientras haya resultados
  int count = 0;
  while (client.available()) {
    char c = client.read();
    if((count++ % 8) == 0) //Imprime un punto por cada byte
      Serial.print(".");
  }
  Serial.println("-");
}

void end_request()
{
  client.stop();
}

void setup() {
  //Inicia la conexión serial con USB
  Serial.begin(9600);
  while (!Serial) { ; }       //Espera la conexión

  //Inicia el proceso de setup
  Serial.println("Setup");

  //Indica que está conectado AREF
  analogReference(EXTERNAL);

  //Inicia el shield de Ethernet con DHCP)
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }else{
    isConnected = true;
  }

  if(!isConnected) {
    Serial.println("Working with no internet connection, dump only");
  }else{
      delay(1000);
  
      Serial.print("IP address: ");
      for (byte thisByte = 0; thisByte < 4; thisByte++) {
        Serial.print(Ethernet.localIP()[thisByte], DEC);
        Serial.print(".");
      }
      Serial.println();
  }

  //Inicia el helper del DHT
  dht.begin();
}

void loop() {

  //Un poco de limpieza
  if(isConnected) {
    Ethernet.maintain();
  
    if (client.available()) {
      client.flush();
    }
  }

  //Lee el sensor de luz
  int lightLevel = analogRead(lightPin);
  lightLevel = 1024 - lightLevel;
  lightLevel = map(lightLevel, 0, 1023, 0, 100);

  //Lee el sensor de temperatura
  int tempReading = analogRead(tempPin);  
 
  //Convierte los valores
  float voltage = tempReading * aref_voltage;
  voltage /= 1024.0; 
  float temperatureC = (voltage - 0.5) * 100 ;

  //Lee la humedad
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //Imprime los valores
  Serial.print(F("Luz: ")); 
  Serial.print(lightLevel); 
  Serial.println(F("%"));

  Serial.print(F("Temp A: ")); 
  Serial.print(temperatureC); 
  Serial.println(F(" C"));

  if (isnan(t) || isnan(h)) {
    Serial.println(F("Failed to read from DHT"));
  }
  else {
    Serial.print(F("Humedad: ")); 
    Serial.println(h);
  }

  //Si está conectado envía los valores por HTTP
  if(isConnected) {
    if (millis() - lastConnectionTime > postingInterval) {

      send_request(temperatureC, h, lightLevel);
      wait_response();
      end_request();
    }
  }

  //Le doy tiempo al DHT entre lecturas
  delay(3000);
}

