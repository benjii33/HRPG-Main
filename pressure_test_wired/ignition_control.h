#ifndef ignition_control_h
#define ignition_control_h

#define IGNITION_COIL_OUT 8
#define IGNITION_COIL_IN 9

void ignition_init();

void set_ignition(bool state, float freq);

void run_ignition(uint32_t currentTime);

#endif