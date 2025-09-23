add_library(
    main
    src/main.cpp
    src/lifecycle/StaticBsp.cpp
    src/systems/BspSystem.cpp)

target_include_directories(main PUBLIC 
    include 
    ../../../application/include 
    ../../../../../libs/bsw/lifecycle/include
)

target_link_libraries(
    main
    PRIVATE asyncBinding
            lifecycle
            bspMcu
            hardFaultHandler
    PUBLIC  bspConfiguration
            bspInputManager
            bspOutputManager)

# RP2040 specific FreeRTOS hooks library
add_library(osHooks src/osHooks.cpp)

target_include_directories(osHooks PRIVATE include)

target_link_libraries(osHooks PRIVATE freeRtos freeRtosRp2040)