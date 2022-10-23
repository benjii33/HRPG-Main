#include "pico/stdlib.h"
#include "ignition_control.h"

uint16_t ignitionPeriod = 0;
bool ignitionState = false;

void ignition_init() {
    // Initialize GPIO to interface with ignition coil
    gpio_init(IGNITION_COIL_OUT);
    gpio_set_dir(IGNITION_COIL_OUT, GPIO_OUT);
    gpio_put(IGNITION_COIL_OUT, 0); // Start coil off

    gpio_init(IGNITION_COIL_IN);
    gpio_set_dir(IGNITION_COIL_IN, GPIO_IN);
}

void set_ignition(bool state, float freq) {
    ignitionState = state;
    ignitionPeriod = (uint16_t)(1000.0/freq);

    // Sanity check - if less than 2, the output would never turn off
    if(ignitionPeriod < 2) {
        ignitionPeriod = 2;
    }
}

// Assumes currentTime takes integer values and increments by 1 every call
// Assumes ignitionPeriod is an integer from 0-255
void run_ignition(uint32_t currentTime) {
    if(currentTime % ignitionPeriod == 0) {
        gpio_put(IGNITION_COIL_OUT, true);
    } else {
        gpio_put(IGNITION_COIL_OUT, false);
    }
}