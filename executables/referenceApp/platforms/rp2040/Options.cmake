set(OPENBSW_PLATFORM rp2040)

# Define platform identifier for conditional compilation
add_compile_definitions(OPENBSW_PLATFORM_RP2040=1)

# Override linker flags to prevent specs file conflicts specific to RP2040
# Remove conflicting nano.specs and nosys.specs 
set(CMAKE_EXE_LINKER_FLAGS "-static -Wl,--gc-sections -Wl,-Map,application.map,--cref -Wl,--noinhibit-exec" CACHE STRING "Linker flags" FORCE)

set(PLATFORM_SUPPORT_IO
    ON
    CACHE BOOL "Turn IO support on or off" FORCE)
set(PLATFORM_SUPPORT_CAN
    OFF
    CACHE BOOL "Turn CAN support on or off" FORCE)
set(PLATFORM_SUPPORT_ETHERNET
    OFF
    CACHE BOOL "Turn ethernet support on or off" FORCE)
set(PLATFORM_SUPPORT_WATCHDOG
    OFF
    CACHE BOOL "Turn ON Watchdog support" FORCE)
set(PLATFORM_SUPPORT_MPU
    OFF
    CACHE BOOL "Turn ON MPU support" FORCE)
set(PLATFORM_SUPPORT_STORAGE
    OFF
    CACHE BOOL "Turn persistent storage on or off" FORCE)
set(PLATFORM_SUPPORT_WIFI
    OFF
    CACHE BOOL "Turn WiFi support on or off" FORCE)
set(PLATFORM_SUPPORT_BLUETOOTH
    OFF
    CACHE BOOL "Turn Bluetooth support on or off" FORCE)