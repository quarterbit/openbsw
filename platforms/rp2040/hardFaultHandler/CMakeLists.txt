add_library(hardFaultHandler src/hardFaultHandler.cpp)

# Note: Removed pico_stdlib dependency - using direct RP2040 register access