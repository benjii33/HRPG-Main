#ifndef solenoid_control_h
#define solenoid_control_h

#define NONE 0

// Enums for defining solenoid relay control pins
typedef enum solenoidPin {
    NITROGEN_PRESS = 6,
    NITROGEN_PURGE = 7,
    ETHANOL_FEED = 8,
    OXYGEN_FEED = 9
} solenoidPin;

typedef enum valveState {
    CLOSED = 1,
    OPEN = 0
} valveState;

void solenoid_init();

void set_solenoid(solenoidPin valve, valveState state);

#endif