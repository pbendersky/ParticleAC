#include <string.h>

// This #include statement was automatically added by the Particle IDE.
#include "ACThermostat.h"

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

#include <HyundaiHeatpumpIR.h>

#include "IRSenderIRRemoteBridge.h"
#include "Homebridge.h"

ACThermostat thermostat;

IRSender *irSender = new IRSenderIRRemoteBridge();
HyundaiHeatpumpIR *heatpumpIR;

void setup() {

    // Disable LED when working normally.
    // See: https://community.particle.io/t/disabling-status-led/3656/17
    LEDSystemTheme theme;
    theme.setColor(LED_SIGNAL_CLOUD_CONNECTED, 0);
    theme.apply();
    
    Particle.function("updateState", updateState);

    heatpumpIR = new HyundaiHeatpumpIR();

    Serial.begin(9600);
}

void loop() {
    Serial.println("loop");
    thermostat.loop();
    delay(thermostat.delayTimeInMilliseconds());
}

int updateState(String data) {
    // data format: this.active, this.mode, this.fanSpeed, this.targetTemperature, this.swingMode
    Serial.println("updateState");
    Serial.println(data);
    
    const char *dataString;
    char *tokenizable, *token;
    
    dataString = data.c_str();
    
    tokenizable = strdup(dataString);
    
    int active, mode, fanSpeed, targetTemperature, swingMode;

    // Parse parameters
    
    if ((token = strsep(&tokenizable, "|")) != NULL) {
        active = atoi(token);
    }
    if ((token = strsep(&tokenizable, "|")) != NULL) {
        mode = atoi(token);
    }
    if ((token = strsep(&tokenizable, "|")) != NULL) {
        fanSpeed = atoi(token);
    }
    if ((token = strsep(&tokenizable, "|")) != NULL) {
        targetTemperature = atoi(token);
    }
    if ((token = strsep(&tokenizable, "|")) != NULL) {
        swingMode = atoi(token);
    }
    
    free(tokenizable);
    
    // Translate from Homebridge constants to HeatpumpIR constants
    
    active = (active == HB_Characteristic_Active_ACTIVE) ? POWER_ON : POWER_OFF;
    switch(mode) {
        case HB_Characteristic_TargetHeaterCoolerState_AUTO:
            mode = MODE_AUTO;
            break;
        case HB_Characteristic_TargetHeaterCoolerState_HEAT:
            mode = MODE_HEAT;
            break;
        case HB_Characteristic_TargetHeaterCoolerState_COOL:
            mode = MODE_COOL;
            break;
    }
    switch(fanSpeed) {
        case 0:
            fanSpeed = FAN_AUTO;
            break;
        case 25:
            fanSpeed = FAN_AUTO;
            break;
        case 50:
            fanSpeed = FAN_1;
            break;
        case 75:
            fanSpeed = FAN_2;
            break;
        case 100:
            fanSpeed = FAN_3;
            break;
    }
    swingMode = (swingMode == HB_Characteristic_SwingMode_SWING_ENABLED) ? VDIR_SWING : VDIR_MANUAL;

    heatpumpIR->send(*irSender, active, mode, fanSpeed, targetTemperature, swingMode, HDIR_AUTO);

    return 0;
}
