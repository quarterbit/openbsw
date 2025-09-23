# FreeRTOS RP2040 Port
# This provides the FreeRTOS port implementation for RP2040

add_library(freeRtosRp2040 src/port.c)

target_include_directories(freeRtosRp2040 PUBLIC include)

# This provides the port implementation that the main freeRtos library will use
# The main freeRtos library from libs/3rdparty/freeRtos will link to this