# RP2040 BSP Modules

add_subdirectory(bspMcu)
add_subdirectory(bspIo)
add_subdirectory(bspInterruptsImpl)
# add_subdirectory(bspSyscalls) # Using existing syscalls in bspCore/platformSyscalls.cpp

# TODO: Add other BSP modules as they are implemented
# add_subdirectory(bspClock)
add_subdirectory(bspCore)
# add_subdirectory(bspAdc)
# add_subdirectory(bspPwm)
# add_subdirectory(bspUart)
# add_subdirectory(bspSpi)
# add_subdirectory(bspI2c)

add_library(socBsp INTERFACE)
target_link_libraries(
    socBsp
    INTERFACE bspMcu
              bspIo
              bspCore
              bspInterruptsImpl)

# Note: Removed pico_stdlib dependency to follow OpenBSW pattern
# Direct hardware register access will be used instead