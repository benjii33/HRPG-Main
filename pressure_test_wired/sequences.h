#ifndef sequences_h
#define sequences_h

#include "sequencing.h"
#include "solenoid_control.h"

// Sequence. All times in ms
actionSequence full_sequence_basic = {14, // 14 steps long
    {{10, VALVE_CONTROL, {ETHANOL_FEED, CLOSED}}, // Close ETH feed [START CLOSED]
    {10, VALVE_CONTROL, {OXYGEN_FEED, CLOSED}}, // Close O2 feed
    {50, VALVE_CONTROL, {NITROGEN_PURGE, CLOSED}}, // Close N2 purge
    {50, IGNITION_CONTROL, {OFF, 0}}, // Turn off ignition
    {100, VALVE_CONTROL, {NITROGEN_PRESS, OPEN}}, // Open N2 pressurization, give time to pressurize [BEGIN SEQUENCE]
    {1000, IGNITION_CONTROL, {ON, 0}}, // Turn on ignition
    {1010, VALVE_CONTROL, {ETHANOL_FEED, OPEN}}, // Open ETH feed
    {1010, VALVE_CONTROL, {OXYGEN_FEED, OPEN}}, // Open O2 feed
    {1800, IGNITION_CONTROL, {OFF, 0}}, // Turn off ignition [RUNNING STATE]
    {3000, VALVE_CONTROL, {OXYGEN_FEED, CLOSED}}, // Turn off O2 feed after 2 seconds of open [END FIRE]
    {3000, VALVE_CONTROL, {ETHANOL_FEED, CLOSED}}, // Turn off ETH feed
    {3200, VALVE_CONTROL, {NITROGEN_PRESS, CLOSED}}, // Close N2 pressurization
    {3500, VALVE_CONTROL, {NITROGEN_PURGE, OPEN}}, // Open N2 purge [PURGE]
    {6500, VALVE_CONTROL, {NITROGEN_PURGE, CLOSED}}} // Close N2 purge [END SEQUENCE]
};


#endif