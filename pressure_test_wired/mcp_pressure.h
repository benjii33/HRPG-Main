#ifndef mcp_pressure_h
#define mcp_pressure_h

uint16_t mcp0Read(uint adc_chan);

void pressure_init();

float get_pressure(uint8_t chan);

#endif