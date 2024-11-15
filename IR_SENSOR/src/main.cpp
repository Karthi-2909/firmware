#include <Arduino.h>
#include <ArduinoJson.h>
#define IR_SENSOR 4
#define LED 2
void irSensor();
String cid();
void irJsonData(bool getIrData,String getDeviceId);
void setup()
{
  Serial.begin(9600);
  pinMode(IR_SENSOR,INPUT);
  pinMode(LED,OUTPUT);
}
void loop()
{
 irSensor();
}
void irSensor()
{
  String did=cid();
  bool irData= digitalRead(IR_SENSOR);
  
  if(irData == false)
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
     digitalWrite(LED,LOW);
  }
  irJsonData(irData,did);
}
String cid()
{
 uint64_t chipid;  
 chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length:6bytes)
 String ID_Second  = String(uint16_t(chipid),HEX);
 String ID_first   = String(uint32_t(chipid>>16),HEX); 
 ID_first.toUpperCase();
 ID_Second.toUpperCase();
 String DEVICE_ID = String(ID_first)+String(ID_Second);
 return(DEVICE_ID);
}

void irJsonData(bool getIrData,String getDeviceId)
{
  JsonDocument data;
  String buffer;
  data["object"] = getIrData;
  data["deviceid"] = getDeviceId;
  serializeJson(data,buffer);
  Serial.println(buffer);
  delay(1000);
}
