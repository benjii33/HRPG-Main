#ifndef sequences_h
#define sequences_h

#include "sequencing.h"
#include "solenoid_control.h"

// Sequence. All times in ms
actionSequence full_sequence_basic = {16, // 16 steps long
    {{10, VALVE_CONTROL, {ETHANOL_FEED, CLOSED}}, // Close ETH feed [START CLOSED]
    {10, VALVE_CONTROL, {OXYGEN_FEED, CLOSED}}, // Close O2 feed
    {15, VALVE_CONTROL, {NITROGEN_PURGE, CLOSED}}, // Close N2 purge
    {16, IGNITION_CONTROL, {OFF, 0}}, // Turn off ignition
    {5000, VALVE_CONTROL, {NITROGEN_PRESS, OPEN}}, // Open N2 pressurization, give time to pressurize [BEGIN SEQUENCE]
    {154000, VALVE_CONTROL, {NITROGEN_PURGE, CLOSED}}, // Close N2 purge
    {159000, VALVE_CONTROL, {NITROGEN_PURGE, CLOSED}}, // Close N2 purge
    {163000, IGNITION_CONTROL, {ON, 0}}, // Turn on ignition
    {161000, VALVE_CONTROL, {ETHANOL_FEED, OPEN}}, // Open ETH feed
    {161000, VALVE_CONTROL, {OXYGEN_FEED, OPEN}}, // Open O2 feed
    {170000, IGNITION_CONTROL, {OFF, 0}}, // Turn off ignition [RUNNING STATE]
    {171000, VALVE_CONTROL, {OXYGEN_FEED, CLOSED}}, // Turn off O2 feed after 2 seconds of open [END FIRE]
    {171000, VALVE_CONTROL, {ETHANOL_FEED, OPEN}}, // Turn off ETH feed
    {172000, VALVE_CONTROL, {NITROGEN_PRESS, CLOSED}}, // Close N2 pressurization
    {173000, VALVE_CONTROL, {NITROGEN_PURGE, OPEN}}, // Open N2 purge [PURGE]
    {180000, VALVE_CONTROL, {NITROGEN_PURGE, CLOSED}}} // Close N2 purge [END SEQUENCE]
};

actionSequence valve_test = {8, // 8 steps long
    {{100, VALVE_CONTROL, {ETHANOL_FEED, OPEN}},
    {2000, VALVE_CONTROL, {NITROGEN_PRESS, OPEN}},
    {4000, VALVE_CONTROL, {OXYGEN_FEED, OPEN}},
    {6000, VALVE_CONTROL, {NITROGEN_PURGE, OPEN}},
    {8000, VALVE_CONTROL, {ETHANOL_FEED, CLOSED}},
    {10000, VALVE_CONTROL, {NITROGEN_PRESS, CLOSED}},
    {12000, VALVE_CONTROL, {OXYGEN_FEED, CLOSED}},
    {14000, VALVE_CONTROL, {NITROGEN_PURGE, CLOSED}}}
};

actionSequence ignition_test = {2, // 2 steps long
    {{10, IGNITION_CONTROL, {ON, 0}},
    {5000, IGNITION_CONTROL, {OFF, 0}}}
};


#endif