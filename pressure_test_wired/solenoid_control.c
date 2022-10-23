#include "pico/stdlib.h"
#include "solenoid_control.h"

void solenoid_init() {
    // Initialize GPIO to interface with relay board
    gpio_init(NITROGEN_PRESS);
    gpio_set_dir(NITROGEN_PRESS, GPIO_OUT);
    gpio_put(NITROGEN_PRESS, 0);

    gpio_init(NITROGEN_PURGE);
    gpio_set_dir(NITROGEN_PURGE, GPIO_OUT);
    gpio_put(NITROGEN_PURGE, 0);

    gpio_init(ETHANOL_FEED);
    gpio_set_dir(ETHANOL_FEED, GPIO_OUT);
    gpio_put(ETHANOL_FEED, 0);

    gpio_init(OXYGEN_FEED);
    gpio_set_dir(OXYGEN_FEED, GPIO_OUT);
    gpio_put(OXYGEN_FEED, 0);
}

void set_solenoid(solenoidPin valve, valveState state) {
    gpio_put(valve, state);
}