#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "pico/time.h"
#include "mcp_pressure.h"

int main() {
    stdio_init_all();
    
    // Initialize pin 15 as relay control.
    // Important to do this step early so solenoid outputs are well-behaved
    gpio_init(15);
    gpio_set_dir(15, 1);
    gpio_put(15, 0);

    pressure_init();

    uint32_t time_ms = 0;
    absolute_time_t timeout_time;

    // 1ms loop
    while (1) {
        timeout_time = make_timeout_time_us(1000); // 1000 us (1 ms) loop time
        
        float pressure = get_pressure(1); // Read from channel 1

        printf("Pressure: %f\n", pressure);


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