add_executable(relay_test
    relay_test.c
)

pico_set_program_name(relay_test "relay_test")
pico_set_program_version(relay_test "0.1")

# Add the necessary libraries to the build
target_link_libraries(relay_test
    pico_stdlib
    hardware_spi
    hardware_pio
    hardware_clocks
)

# enable usb output, disable uart output
pico_enable_stdio_usb(relay_test 1)
pico_enable_stdio_uart(relay_test 0)

pico_add_extra_outputs(relay_test)
