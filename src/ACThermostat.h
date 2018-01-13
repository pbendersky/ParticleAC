#ifndef ACThermostat_h
#define ACThermostat_h

#include <Adafruit_DHT.h>

class ACThermostat {
    DHT dht;
    double currentTemperature;
    double currentHumidity;

public:
    ACThermostat();
    void loop();
    long delayTimeInMilliseconds();
private:
    void updateFromDHTSensor();
};

#endif // #ifndef ACThermostat
