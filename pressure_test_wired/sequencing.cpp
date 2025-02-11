#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "sequencing.h"
#include "solenoid_control.h"
#include "ignition_control.h"

void runAction(sequenceItem action) {
    if(action.cmd == VALVE_CONTROL) {
        printf("Set valve %i to state %i\n", action.args[0], action.args[1]);
        set_solenoid((solenoidPin)action.args[0], (valveState)action.args[1]);
    } else if(action.cmd == IGNITION_CONTROL) {
        printf("Set ignition to state %i\n", action.args[0]);
        set_ignition(action.args[0], 10);
    }
}

// Iterate through sequence and execute all actions matching current time
void runSequence(actionSequence sequence, uint32_t currentTime) {
    for(uint8_t i = 0; i < sequence.length; i++) {
        sequenceItem action = sequence.cmd[i];
        if(action.timeStamp == currentTime) {
            printf("At time %i, running action: ", currentTime);
            runAction(action);
        }
    }
}