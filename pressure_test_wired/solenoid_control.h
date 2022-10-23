#ifndef solenoid_control_h
#define solenoid_control_h

#define NONE 0

// Enums for defining solenoid relay control pins
typedef enum solenoidPin {
    NITROGEN_PRESS = 4,
    NITROGEN_PURGE = 5,
    ETHANOL_FEED = 6,
    OXYGEN_FEED = 7
} solenoidPin;

typedef enum valveState {
    CLOSED = 0,
    OPEN = 1
} valveState;

void solenoid_init();

void set_solenoid(solenoidPin valve, valveState state);

#endif