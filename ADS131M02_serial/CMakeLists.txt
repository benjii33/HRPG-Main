add_executable(ADS131M02_serial
    ADS131M02_serial.c
)

pico_set_program_name(ADS131M02_serial "ADS131M02_serial")
pico_set_program_version(ADS131M02_serial "0.1")

pico_generate_pio_header(ADS131M02_serial ${CMAKE_CURRENT_LIST_DIR}/clock.pio)

# Add the necessary libraries to the build
target_link_libraries(ADS131M02_serial
    pico_stdlib
    hardware_spi
    hardware_pio
    hardware_clocks
)

# enable usb output, disable uart output
pico_enable_stdio_usb(ADS131M02_serial 1)
pico_enable_stdio_uart(ADS131M02_serial 0)

pico_add_extra_outputs(ADS131M02_serial)
