# RP2040 Platform CMake Configuration

# Define platform macro for conditional compilation
add_definitions(-DPLATFORM_RP2040)

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