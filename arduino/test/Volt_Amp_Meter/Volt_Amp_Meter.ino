#include <Wire.h> 
#define VT_PIN A0 // connect VT
#define AT_PIN D2 // connect AT
#define ARDUINO_WORK_VOLTAGE 3.0

void setup()

{
  Serial.begin(115200);
  for(int i;i++;i<5)
  {
    Serial.print("Wait");
    Serial.println(i);
  }
}
void loop()
{
  int vt_temp = analogRead(VT_PIN);
  int at_temp = analogRead(AT_PIN);
  double voltage = vt_temp * (ARDUINO_WORK_VOLTAGE / 1023.0) * 5;
  double current = at_temp * (ARDUINO_WORK_VOLTAGE / 1023.0);
  Serial.print("Voltage");
  Serial.print(voltage);
  Serial.print("     ");
  Serial.print("Current");
  Serial.println(current);
  delay(500);
}

