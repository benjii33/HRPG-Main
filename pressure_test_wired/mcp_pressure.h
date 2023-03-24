#ifndef mcp_pressure_h
#define mcp_pressure_h

#define chamber_trans 3
#define ethanol_trans 2
#define oxygen_trans 1
#define nitrogen_trans 0

uint16_t mcp0Read(uint adc_chan);

void pressure_init();

float get_pressure(uint8_t chan);

#endif