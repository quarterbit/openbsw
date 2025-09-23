# RP2040 Platform CMake Configuration

# Ensure C language is enabled for FreeRTOS port
enable_language(C)

# 3rdparty modules
add_subdirectory(3rdparty/freertos_rp2040)

# BSP modules
add_subdirectory(bsp)

# Other modules
add_subdirectory(hardFaultHandler)
if (PLATFORM_SUPPORT_ETHERNET)
    add_subdirectory(lwipSysArch)
endif()