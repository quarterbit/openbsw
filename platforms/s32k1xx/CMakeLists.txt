# S32K1xx Platform CMake Configuration

# Define platform macro for conditional compilation  
add_definitions(-DPLATFORM_S32K148EVB)

# 3rdparty modules
add_subdirectory(3rdparty/freertos_cm4_sysTick)

# BSP modules
add_subdirectory(bsp)

# Other modules
add_subdirectory(hardFaultHandler)
add_subdirectory(lwipSysArch)
