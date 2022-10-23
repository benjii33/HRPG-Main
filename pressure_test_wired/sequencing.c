#include "pico/stdlib.h"
#include "sequencing.h"
#include "solenoid_control.h"
#include "ignition_control.h"

void runAction(sequenceItem action) {
    if(action.cmd == VALVE_CONTROL) {
        set_solenoid(action.args[0], action.args[1]);
    } else if(action.cmd == IGNITION_CONTROL) {
        set_ignition(action.args[0], 5);
    }
}

// Iterate through sequence and execute all actions matching current time
void runSequence(actionSequence sequence, uint32_t currentTime) {
    for(uint8_t i = 0; i < sequence.length; i++) {
        sequenceItem action = sequence.cmd[i];
        if(action.timeStamp == currentTime) {
            runAction(action);
        }
    }
}