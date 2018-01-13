// This #include statement was automatically added by the Particle IDE.
#include "ACThermostat.h"

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

#include <HyundaiHeatpumpIR.h>

#define IR_PIN D6
#define LED_PIN D7

ACThermostat thermostat;

// typedef enum {
//     Off,
//     Heat,
//     Cool,
//     Auto
// } PowerMode;

// typedef struct {
//     PowerMode powerMode;
//     float targetTemperature; // In Celcius
//     float currentTemperature; // In Celcius
//     float currentHumidity;
// } ACState;

// ACState currentACState;

IRSenderBitBang irSender(D6);
HyundaiHeatpumpIR *heatpumpIR;

void setup() {
    Particle.function("powerOn", powerOn);
    Particle.function("powerOff", powerOff);

    heatpumpIR = new HyundaiHeatpumpIR();

    Serial.begin(9600);
}

void loop() {
    Serial.println("loop");
    thermostat.loop();
    delay(thermostat.delayTimeInMilliseconds());
}

int powerOn(String data) {
    Serial.println("powerOn");
    /*transmitter.Transmit(ac_on, sizeof(ac_on) / sizeof(unsigned int));*/
    /*irsend.sendNEC(0x3EA0000A, 32);*/
    heatpumpIR->send(irSender, POWER_ON, MODE_COOL, FAN_1, 24, VDIR_AUTO, HDIR_AUTO);

    return 0;
}

int powerOff(String data) {
    /*irsend.sendLG(0x88C0051, 28);*/
    heatpumpIR->send(irSender, POWER_OFF, MODE_COOL, FAN_1, 24, VDIR_AUTO, HDIR_AUTO);

    return 0;
}

