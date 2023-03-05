add_executable(pressure_test_wired
    pressure_test_wired.cpp
    mcp_pressure.cpp
    solenoid_control.cpp
    ignition_control.cpp
    sequencing.cpp
    LoRa-RP2040.cpp
    Print.cpp
)

pico_set_program_name(pressure_test_wired "pressure_test_wired")
pico_set_program_version(pressure_test_wired "0.1")

# Add the necessary libraries to the build
target_link_libraries(pressure_test_wired
    pico_stdlib
    pico_time
    hardware_spi
    hardware_pio
    hardware_clocks
)

# enable usb output, disable uart output
pico_enable_stdio_usb(pressure_test_wired 1)
pico_enable_stdio_uart(pressure_test_wired 0)

pico_add_extra_outputs(pressure_test_wired)
