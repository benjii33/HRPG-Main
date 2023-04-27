#ifndef thrust_sense_h
#define thrust_sense_h

#include "pico/stdlib.h"

#define HX711_DAT 13
#define HX711_CLK 12

extern bool measurement_in_progress;
extern int32_t channel_A;
extern int32_t channel_B;

// Set up HX711 thrust measurement
void HX711_init();

// Read thrust using HX711 and load cells
int32_t read_thrust();

// Read data from HX711. Suffix should be 1 for A.128, 2 for B.32, and 3 for A.64
int32_t HX711_read(uint8_t suffix);

#endif