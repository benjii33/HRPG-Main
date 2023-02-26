#ifndef solenoid_control_h
#define solenoid_control_h

#define NONE 0

// Enums for defining solenoid relay control pins
typedef enum solenoidPin {
    NITROGEN_PRESS = 6,
    NITROGEN_PURGE_O2 = 10,
    NITROGEN_PURGE_ET = 7,
    ETHANOL_FEED = 8,
    OXYGEN_FEED = 11
} solenoidPin;

typedef enum valveState {
    CLOSED = 0,
    OPEN = 1
} valveState;

void solenoid_init();

void set_solenoid(solenoidPin valve, valveState state);

#endif