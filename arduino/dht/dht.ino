#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
int DHTPIN = 2;          //setpin of DHT at D0
int DHTTYPE = DHT11;     //set Dht Type 
DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "SmartMushroomBox";            //Set ssid
const char* password = "12345678";                    //Set Password
const char* Server   = "139.59.99.17";           //set Server Domain or Server ip
const char* Port     = "8000";
const char* nodeid   = "1"
const char* sensorname = "dht";                        
ESP8266WiFiMulti WiFiMulti;
void setup()
{
  Serial.begin(115200);
  for(uint8_t t = 6; t > 0; t--) 
      {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
      }
    WiFiMulti.addAP(ssid, password);    //Set SSID and Password (SSID, Password)
    WiFi.begin(ssid, password);         //Set starting for Wifi
    Serial.println(WiFi.localIP());
    dht.begin();
}
void loop() 
{
  float h = dht.readHumidity();      //Read Humidity
  float t = dht.readTemperature();   //Read Temperature
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("FaiLed to read from DHT");
  } 
  else 
  {
    Serial.print("Temp");
    Serial.print(t);
    Serial.println("*c");
    Serial.print("Humi");
    Serial.print(h);
    Serial.print("%");
    SendData(h,t);
  }
  delay(1000);
}

void SendData(float h,float t) 
{
  
  // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) 
    {
        HTTPClient http;
        String str = "http://" +String(Server)+":"+String(Port)+"/data"+"/"+String(nodeid)+"/"+String(sensorname)+"/"+ String(t)+"/"+String(h);
        Serial.println(str);
        http.begin(str);
        int httpCode = http.GET();
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        if(httpCode > 0) 
        {
            if(httpCode == HTTP_CODE_OK) 
              {
                String payload = http.getString();
      //-------------------Control----------------------------//
                Serial.print("payload");
                Serial.println(payload);
              }
        }
    }
}
