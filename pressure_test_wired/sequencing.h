#ifndef sequencing_h
#define sequencing_h

#include "pico/stdlib.h"

#define OFF 0
#define ON 1

typedef enum sequenceCommand {
    VALVE_CONTROL = 1,
    IGNITION_CONTROL = 2,
} sequenceCommand;

// Struct to create test sequences 
typedef struct sequenceItem {
    uint32_t timeStamp;
    sequenceCommand cmd;
    uint8_t args[2]; // Arguments of command such as which solenoid
} sequenceItem;

// Struct to create test sequences 
typedef struct actionSequence {
    uint8_t length;
    sequenceItem cmd[17];
} actionSequence;

void runSequence(actionSequence sequence, uint32_t currentTime);

#endif