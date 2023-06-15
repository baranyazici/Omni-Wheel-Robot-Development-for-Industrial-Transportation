
#include <SoftwareSerial.h>
SoftwareSerial(A8,38); // RX, TX
int data


void setup() 
{
  Bluetooth.begin(9600);
  Serial.begin(9600);

}

void loop() 
{
  if(Bluetooth.available())
  {
    Data = Bluetooth.read();
    Serial.println(Data);
  }

}
