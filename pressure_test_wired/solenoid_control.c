#include "pico/stdlib.h"
#include "solenoid_control.h"

void solenoid_init() {
    // Initialize GPIO to interface with relay board
    gpio_init(NITROGEN_PRESS);
    gpio_set_dir(NITROGEN_PRESS, GPIO_OUT);
    gpio_put(NITROGEN_PRESS, CLOSED);

    gpio_init(NITROGEN_PURGE);
    gpio_set_dir(NITROGEN_PURGE, GPIO_OUT);
    gpio_put(NITROGEN_PURGE, CLOSED);

    // gpio_init(NITROGEN_PURGE_ET);
    // gpio_set_dir(NITROGEN_PURGE_ET, GPIO_OUT);
    // gpio_put(NITROGEN_PURGE_ET, CLOSED);

    gpio_init(ETHANOL_FEED);
    gpio_set_dir(ETHANOL_FEED, GPIO_OUT);
    gpio_put(ETHANOL_FEED, CLOSED);

    gpio_init(OXYGEN_FEED);
    gpio_set_dir(OXYGEN_FEED, GPIO_OUT);
    gpio_put(OXYGEN_FEED, CLOSED);
}

void set_solenoid(solenoidPin valve, valveState state) {
    gpio_put(valve, state);
}