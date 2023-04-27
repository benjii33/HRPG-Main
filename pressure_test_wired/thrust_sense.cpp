#include "pico/stdlib.h"
#include "thrust_sense.h"

int32_t channel_A;
int32_t channel_B;
bool measurement_in_progress;

void HX711_init() {
    // Set up force feedback
    gpio_init(HX711_DAT);
    gpio_init(HX711_CLK);
    gpio_set_dir(HX711_DAT, false);
    gpio_set_dir(HX711_CLK, true);
    gpio_put(HX711_CLK, false);

    measurement_in_progress = false;
    channel_A = 0;
    channel_B = 0;
}

int32_t read_thrust() {
    if(gpio_get(HX711_DAT)) { // If measurement not ready, return
        return 0;
    }

    if(!measurement_in_progress) { // Begin new thrust measurement
        channel_A = HX711_read(2); // We want channel B next
        measurement_in_progress = true;

    } else { // Took channel A measurement, ready to take B
        channel_B = HX711_read(3); // Take channel A on next round
        measurement_in_progress = false;

        int32_t thrust = channel_A + 2*channel_B; // Channel B has 32x amplification, A has 64x
        return thrust;
    }
    return 0; // Data not ready yet
}

int32_t HX711_read(uint8_t suffix) {
    int32_t force = 0;

    while(gpio_get(HX711_DAT)); // Stall until DAT goes low

    // Shift in data
    for(uint8_t i = 0; i < 24; i++) {
        gpio_put(HX711_CLK, true);
        sleep_us(1);
        force = force | gpio_get(HX711_DAT) << (23 - i);
        gpio_put(HX711_CLK, false);
        sleep_us(1);
    }
    for(uint8_t i = 0; i < suffix; i++) { // Wiggle CLK to set channel and gain for next measurement
        gpio_put(HX711_CLK, true);
        sleep_us(1);
        gpio_put(HX711_CLK, false);
        sleep_us(1);
    }

    force = force & 0x0FFF;

    return force;
}