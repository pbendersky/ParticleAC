#include "ACThermostat.h"

#include "application.h"

#include <Adafruit_DHT.h>

#define DHTPIN 2     // what pin we're connected to

#define DHTTYPE DHT22		// DHT 22 (AM2302)

ACThermostat::ACThermostat() : dht(DHTPIN, DHTTYPE) {
    Particle.variable("currentTemp", currentTemperature);
    Particle.variable("currentHumid", currentHumidity);
    dht.begin();
}

void ACThermostat::loop() {
    updateFromDHTSensor();
}

long ACThermostat::delayTimeInMilliseconds() {
    return 2000;
}

void ACThermostat::updateFromDHTSensor() {
    Serial.println("updateFromDHTSensor");
    currentHumidity = (double)dht.getHumidity();
    currentTemperature = (double)dht.getTempCelcius();
    Serial.println(dht.getTempCelcius());
}
