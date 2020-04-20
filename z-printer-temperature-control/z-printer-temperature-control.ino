#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_PIN 2
#define HEATER_PIN 4

#define TEMPERATURE_DELTA_CELSIUS 0.25
#define TEMPERATURE_LIMIT_CELSIUS 37.778

OneWire oneWire(SENSOR_PIN);
DallasTemperature sensors(&oneWire);

bool heating = false;

void setup() {
  pinMode(HEATER_PIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Z Printer Temperature Control");
  Serial.println("Revived by the Fall 2018 Section of ARCH 497");
  sensors.begin();
}

void loop() {
  
  sensors.requestTemperatures();
  
  float temp = sensors.getTempCByIndex(0);

  // prevent heater from switching on/off repeatedly
  if (temp > TEMPERATURE_LIMIT_CELSIUS + TEMPERATURE_DELTA_CELSIUS) {
    heating = false;
  } else if (temp < TEMPERATURE_LIMIT_CELSIUS - TEMPERATURE_DELTA_CELSIUS) {
    heating = true;
  }

    
  Serial.print("Temperature is ");
  Serial.print(temp);
  Serial.print("ºC, so the heater is ");
  Serial.println(heating ? "ON." : "OFF.");
  
  digitalWrite(HEATER_PIN, (heating) ? HIGH : LOW);
   
}
