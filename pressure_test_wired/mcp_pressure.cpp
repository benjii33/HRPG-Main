#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mcp_pressure.h"
#include "spi_connections.h"

static inline void cs_select() {
    asm volatile("nop \n nop \n nop");
    gpio_put(MCP_CS, 0);  // Active low
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect() {
    asm volatile("nop \n nop \n nop");
    gpio_put(MCP_CS, 1);
    asm volatile("nop \n nop \n nop");
}

uint16_t mcp0Read(uint adc_chan) {
  uint8_t writebuf[] = {0b00000110, 0b00000000, 0x00};
  writebuf[1] |= (adc_chan << 6) & 0b11000000;
  writebuf[0] |= (adc_chan >> 2) & 0b00000001;
  uint8_t readbuf[] = {0x00, 0x00, 0x00};

  cs_select();
  spi_write_read_blocking(SPI_PORT, writebuf, readbuf, 3);
  cs_deselect();

  readbuf[1] &= 0b00001111;
  return (readbuf[1]<<8) | readbuf[2];
}

void pressure_init() {
    // We will use SPI0 at 1.5MHz.
    spi_init(SPI_PORT, 1500 * 1000);
    spi_set_format(SPI_PORT, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST); // was 1, 1
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_init(MCP_CS);
    gpio_set_dir(MCP_CS, GPIO_OUT);
    gpio_put(MCP_CS, 1);
}

// Returns pressure in PSI 
float get_pressure(uint8_t chan) {
    uint16_t sample = mcp0Read(chan);

    // Resolution: 256 (8-bit) 1024 (10-bit) 4096 (12-bit)
    float voltage = (sample / 4096.0) * 3.3;
    float pressure = (voltage * 124.0) - 63.0;

    return pressure;
}
