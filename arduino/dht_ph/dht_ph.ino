#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
///////////////////////////////////////////////////////////////////////////////////////////
#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset -6.3            //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;
///////////////////////////////////////////////////////////////////////////////////////////
int DHTPIN = 2;          //setpin of DHT at D0
int DHTTYPE = DHT11;     //set Dht Type 
DHT dht(DHTPIN, DHTTYPE);
void SendData(float h,float t,float pHValue);
double avergearray(int* arr, int number);

const char* ssid     = "true_home2G_792";            //Set ssid
const char* password = "ilovestudy";                    //Set Password
const char* Server   = "192.168.1.36";           //set Server Domain or Server ip
const char* Port     = "8000";
const char* nodeid   = "3";
const char* sensorname = "dht_ph";                        
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
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
  Serial.print("Voltage:");
  Serial.print(voltage,2);
  Serial.print("    pH value: ");
  Serial.println(pHValue,2);
  printTime=millis();
  }
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
    Serial.println("%");
    SendData(h,t,pHValue);
  }
////////////////////////////////////////////////////////////////////////////////////////////
  
  
////////////////////////////////////////////////////////////////////////////////////////
  delay(1000);
}

void SendData(float h,float t,float pHValue) 
{
  
  // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) 
    {
        HTTPClient http;
        //String str = "http://" +String(Server)+":"+String(Port)+"/data"+"/"+String(nodeid)+"/"+String(sensorname)+"/airtemp/"+ String(t)+"/airhumi/"+String(h)+"/ph/"+String(pHValue);
        String str = "http://" +String(Server)+":"+String(Port)+"/data"+"/"+String(nodeid)+"/airtemp/"+ String(t);
        String str1 = "http://" +String(Server)+":"+String(Port)+"/data"+"/"+String(nodeid)+"/airhumi/"+ String(h);
        String str2 = "http://" +String(Server)+":"+String(Port)+"/data"+"/"+String(nodeid)+"/ph/"+String(pHValue);
        Serial.println(str);
        http.begin(str);
        Serial.println(str1);
        http.begin(str1);
        Serial.println(str2);
        http.begin(str2);
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
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
