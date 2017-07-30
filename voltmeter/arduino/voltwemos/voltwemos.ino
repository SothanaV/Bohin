#include <Wire.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define VT_PIN A0 // connect VT
#define ARDUINO_WORK_VOLTAGE 3.0

void SendData(float v);

const char* ssid     = "true_home2G_792";            //Set ssid
const char* password = "ilovestudy";                    //Set Password
const char* Server   = "192.168.1.54";           //set Server Domain or Server ip
const char* Port     = "8000";
const char* nodeid   = "1";
ESP8266WiFiMulti WiFiMulti;
void setup()
{
  Serial.begin(115200);
  for(int i;i++;i<5)
  {
    Serial.print("Wait");
    Serial.println(i);
  }
  WiFiMulti.addAP(ssid, password);    //Set SSID and Password (SSID, Password)
    WiFi.begin(ssid, password);         //Set starting for Wifi
    Serial.println(WiFi.localIP());
}
void loop()
{
  int vt_temp = analogRead(VT_PIN);
  double voltage = vt_temp * (ARDUINO_WORK_VOLTAGE / 1023.0) * 5;
  Serial.print("Voltage");
  Serial.print(voltage);
  delay(5000);
  float v = voltage;
  SendData(v);
}
void SendData(float v)
{
  if((WiFiMulti.run() == WL_CONNECTED)) 
    {
        HTTPClient http;
        String str = "http://" +String(Server)+":"+String(Port)+"/volt/data"+"/"+String(nodeid)+"/"+String(v);
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

