// Example usage for HeatpumpIR library by Toni Arte.

#include "HeatpumpIR.h"

// Initialize objects from the lib
HeatpumpIR heatpumpIR;

void setup() {
    // Call functions on initialized library objects that require hardware
    heatpumpIR.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    heatpumpIR.process();
}
