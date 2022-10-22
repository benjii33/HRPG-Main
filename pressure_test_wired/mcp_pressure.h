#ifndef mcp_pressure_h
#define mcp_pressure_h

#define PIN_MISO 4
#define PIN_CS   5
#define PIN_SCK  2
#define PIN_MOSI 3

#define SPI_PORT spi0
#define READ_BIT 0x80

uint16_t mcp0Read(uint adc_chan);

void pressure_init();

float get_pressure(uint8_t chan);

#endif