#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/bootrom.h"
#include "LoRa-RP2040.h"
#include "spi_connections.h"
#include "mcp_pressure.h"
#include "solenoid_control.h"
#include "ignition_control.h"
#include "sequences.h"
#include "sequencing.h"
#include "thrust_sense.h"

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

    sleep_ms(5000);

    // LoRa.setPins();

    // if (!LoRa.begin(915e6)) {
	// 	printf("Starting LoRa failed!\n");
	// 	while (1) {
    //         gpio_put(PICO_DEFAULT_LED_PIN, 0);
    //         sleep_ms(20);
    //         gpio_put(PICO_DEFAULT_LED_PIN, 1);
    //         sleep_ms(20);
    //     }
	// }

    char* inputString = (char*)calloc(sizeof(char), 10);
    uint8_t inputIndex = 0;

    uint32_t time_ms = 0;
    absolute_time_t timeout_time;

    // Wait for signal to begin sequence
    while(1) {
        printf("Send any character to begin ignition sequence.\n");
        int16_t inputChar = getchar_timeout_us(0);
        if(inputChar != PICO_ERROR_TIMEOUT) {
            printf("Beginning ignition sequence!\n");
            break;
        }
        sleep_ms(500);
    }

    // 1ms loop
    while(1) {
        timeout_time = make_timeout_time_us(1000); // 1000 us (1 ms) loop time
        
        // Data collection
        if(time_ms%5 == 0) {
            float chamber_pressure = get_pressure(chamber_trans) + 21; //correction factor
            float ethanol_pressure = get_pressure(ethanol_trans);
            float oxygen_pressure = get_pressure(oxygen_trans);
            float nitrogen_pressure = get_pressure(nitrogen_trans) + 63;

            printf("Time: %i | Chamber Pressure: %f | Ethanol Feed Pressure: %f | Oxygen Feed Pressure: %f | Nitrogen Inlet Pressure: %f", time_ms, chamber_pressure, ethanol_pressure, oxygen_pressure, nitrogen_pressure);
        }

        int32_t thrust = read_thrust();
        if(thrust != 0) {
            printf(" | Thrust: %i\n", thrust);
        } else {
            printf("\n");
        }
        
        // Sequencing
        runSequence(full_sequence_basic, time_ms);

        // Ignition control
        run_ignition(time_ms);

        if(time_ms%500 == 0) { // Ping home every half second
            // send packet
            // LoRa.beginPacket();
            // LoRa.print("boing ");
            // LoRa.endPacket();
            // printf("Successfully sent packet\n");
        }

        // Check for received packets
        // int packetSize = LoRa.parsePacket();
        // if (packetSize) {
        //     // received a packet
        //     printf("Received packet \n");

        //     // read packet
        //     while (LoRa.available()) {
        //         // printf((char*)LoRa.read());
        //         printf("%i", LoRa.read());
        //     }

        //     // print RSSI of packet
        //     printf(" with RSSI \n");
        //     printf((char*)LoRa.packetRssi(),"\n");
        // }

        // Running indicator
        // 200ms on, 200ms off blink cycle
        if(time_ms%400 < 200) {
            gpio_put(PICO_DEFAULT_LED_PIN, 1); // blink
        } else {
            gpio_put(PICO_DEFAULT_LED_PIN, 0); // blonk
        }

        // Serial Communications
        int16_t inputChar = getchar_timeout_us(0);
        if(inputChar != PICO_ERROR_TIMEOUT) {
            if(inputChar == '\n') {
                inputString[inputIndex] = '\0';

                // Test input
                if(strcmp("program", inputString) == 0) {
                    printf("This system is going down for reboot NOW!\n");
                    reset_usb_boot(0, 0);
                }

                inputIndex = 0;
                memset(inputString, 0, 10);
            } else {
                inputString[inputIndex] = inputChar & 0xFF;
                inputIndex++;
                inputIndex = inputIndex % 10;
            }
        }

        // Wait until 1 ms loop time has passed
        sleep_until(timeout_time);
        time_ms++;
    }

    return 0;
}