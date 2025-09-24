# S32K1xx Platform CMake Configuration

# Define platform macro for conditional compilation  
# Platform define is now handled in the main CMakeLists.txt

# 3rdparty modules
add_subdirectory(3rdparty/freertos_cm4_sysTick)

# BSP modules
add_subdirectory(bsp)

# Other modules
add_subdirectory(hardFaultHandler)
add_subdirectory(lwipSysArch)
