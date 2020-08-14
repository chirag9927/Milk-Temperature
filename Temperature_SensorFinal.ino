#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
char auth[] = "JniysneQdqjRGDHWsK7C8mq679h0PdlT";
 
/* WiFi credentials */
char ssid[] = "ChiragJain";
char pass[] = "chirag9926";
 
SimpleTimer timer;
 
 
 
#define ONE_WIRE_BUS 2 // DS18B20 on arduino pin2 corresponds to D4 on physical board "D4 pin on the ndoemcu Module"
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float Celsius;
float Fahrenheit=0;
void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  DS18B20.begin();
  timer.setInterval(1000L, getSendData);
}
 
void loop() 
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}
 
/***************************************************
 * Send Sensor data to Blynk
 **************************************************/
void getSendData()
{
  DS18B20.requestTemperatures(); 
  Celsius= DS18B20.getTempCByIndex(0); // Celsius
   Fahrenheit = DS18B20.toFahrenheit(Celsius); // Fahrenheit
  Serial.println(Celsius);
  Serial.println(Fahrenheit);
  Blynk.virtualWrite(V3, Celsius); //virtual pin V3
  Blynk.virtualWrite(V4, Fahrenheit); //virtual pin V4
  if(Celsius>100)
  {
    Blynk.notify(" Milk is about to boil, RUN!!");
  }
}
