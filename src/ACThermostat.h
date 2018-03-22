#ifndef ACThermostat_h
#define ACThermostat_h

#include <Adafruit_DHT.h>

class ACThermostat {
    DHT dht;

public:
    double currentTemperature;
    double currentHumidity;

    ACThermostat();

    void loop();
    long delayTimeInMilliseconds();
private:
    void updateFromDHTSensor();
};

#endif // #ifndef ACThermostat
