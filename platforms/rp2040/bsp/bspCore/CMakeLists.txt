add_library(bspCore 
    src/platformTime.cpp
    src/platformInterrupts.cpp
    src/platformConsole.cpp
    src/platformFreeRTOS.cpp
)

target_include_directories(bspCore PUBLIC include)

target_link_libraries(bspCore PUBLIC bsp freeRtos)