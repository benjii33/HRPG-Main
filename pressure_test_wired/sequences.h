#ifndef sequences_h
#define sequences_h

#include "sequencing.h"
#include "solenoid_control.h"

// Sequence. All times in ms
actionSequence full_sequence_basic = {17, // 17 steps long
    {{10, VALVE_CONTROL, {ETHANOL_FEED, CLOSED}}, // Close ETH feed [START CLOSED]
    {10, VALVE_CONTROL, {OXYGEN_FEED, CLOSED}}, // Close O2 feed
    {15, VALVE_CONTROL, {NITROGEN_PURGE_O2, CLOSED}}, // Close N2 purge
    {15, VALVE_CONTROL, {NITROGEN_PURGE_ET, CLOSED}}, // Close N2 purge
    {16, IGNITION_CONTROL, {OFF, 0}}, // Turn off ignition
    {100, VALVE_CONTROL, {NITROGEN_PRESS, OPEN}}, // Open N2 pressurization, give time to pressurize [BEGIN SEQUENCE]
    {5000, IGNITION_CONTROL, {ON, 0}}, // Turn on ignition
    {5010, VALVE_CONTROL, {ETHANOL_FEED, OPEN}}, // Open ETH feed
    {5010, VALVE_CONTROL, {OXYGEN_FEED, OPEN}}, // Open O2 feed
    {6000, IGNITION_CONTROL, {OFF, 0}}, // Turn off ignition [RUNNING STATE]
    {8000, VALVE_CONTROL, {OXYGEN_FEED, CLOSED}}, // Turn off O2 feed after 2 seconds of open [END FIRE]
    {8000, VALVE_CONTROL, {ETHANOL_FEED, CLOSED}}, // Turn off ETH feed
    {8200, VALVE_CONTROL, {NITROGEN_PRESS, CLOSED}}, // Close N2 pressurization
    {8500, VALVE_CONTROL, {NITROGEN_PURGE_O2, OPEN}}, // Open N2 purge [PURGE]
    {8500, VALVE_CONTROL, {NITROGEN_PURGE_ET, OPEN}}, // Open N2 purge [PURGE]
    {10500, VALVE_CONTROL, {NITROGEN_PURGE_O2, CLOSED}}, // Close N2 purge
    {10500, VALVE_CONTROL, {NITROGEN_PURGE_ET, CLOSED}}} // Close N2 purge [END SEQUENCE]
};


#endif