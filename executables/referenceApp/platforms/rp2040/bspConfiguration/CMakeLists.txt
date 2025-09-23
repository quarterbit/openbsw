add_library(bspConfiguration 
    src/bsp/adc/AnalogInput.cpp
)

target_include_directories(bspConfiguration PUBLIC include)

target_link_libraries(
    bspConfiguration
    PUBLIC socBsp  # Our basic BSP library
           hardFaultHandler
           bspInputManager
           bspOutputManager
           bspOutputPwm
           bspInterrupts
           bspCore)