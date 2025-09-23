add_subdirectory(bspConfiguration)
add_subdirectory(freeRtosCoreConfiguration)
add_subdirectory(main)

# Use RP2040 FreeRTOS port
add_library(freeRtosPort ALIAS freeRtosRp2040)
add_library(freeRtosPortImpl ALIAS freeRtosRp2040)