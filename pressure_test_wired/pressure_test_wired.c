#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "mcp_pressure.h"
#include "solenoid_control.h"
#include "ignition_control.h"
#include "sequences.h"
#include "sequencing.h"

int main() {
    stdio_init_all();
    
    // Initialize solenoid relay and ignition control pins
    // Important to do this step early so solenoid/ignition outputs are well-behaved
    ignition_init();
    solenoid_init();

    // Start indicator LED as on
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    pressure_init();

    uint32_t time_ms = 0;
    absolute_time_t timeout_time;

    // 1ms loop
    while (1) {
        timeout_time = make_timeout_time_us(1000); // 1000 us (1 ms) loop time
        
        // Data collection
        float pressure = get_pressure(1); // Read from channel 1
        printf("Pressure: %f\n", pressure);

        // Sequencing
        runSequence(full_sequence_basic, time_ms);

        // Ignition control
        run_ignition(time_ms);

        // Running indicator
        // 20ms on, 20ms off blink cycle
        if(time_ms%40 < 20) {
            gpio_put(PICO_DEFAULT_LED_PIN, 1); // blink
        } else {
            gpio_put(PICO_DEFAULT_LED_PIN, 0); // blonk
        }

        // Wait until 1 ms loop time has passed
        sleep_until(timeout_time);
        time_ms++;
    }

    return 0;
}