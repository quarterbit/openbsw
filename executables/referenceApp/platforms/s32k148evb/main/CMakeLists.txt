add_library(
    startUp
    src/bsp/bootHeader.S
    src/bsp/startUp.S
    src/os/isr/isr_can.cpp
    src/os/isr/isr_enet.cpp
    src/os/isr/isr_erm.cpp
    src/os/isr/isr_ftfc.cpp
    src/os/isr/isr_sys.cpp
    src/os/isr/isr_wdg.cpp)

target_link_libraries(startUp PRIVATE bspMcu common hardFaultHandler)

# Define platform support macros for ISR files
if (PLATFORM_SUPPORT_CAN)
    target_compile_definitions(startUp PRIVATE PLATFORM_SUPPORT_CAN)
endif ()

if (PLATFORM_SUPPORT_ETHERNET)
    target_compile_definitions(startUp PRIVATE PLATFORM_SUPPORT_ETHERNET)
endif ()

set(mainSources
    src/systems/BspSystem.cpp
    src/lifecycle/StaticBsp.cpp
    src/main.cpp)

if (PLATFORM_SUPPORT_CAN)
    list(APPEND mainSources src/systems/CanSystem.cpp)
endif ()

if (PLATFORM_SUPPORT_ETHERNET)
    list(APPEND mainSources src/systems/S32K148EvbEthernetSystem.cpp)
endif ()

add_library(
    main
    ${mainSources})

target_include_directories(main PUBLIC include)

target_link_libraries(
    main
    PRIVATE asyncConsole
            bsp
            bspClock
            bspCore
            bspTja1101
            bspMcuWatchdog
            canflex2Transceiver
            configuration
            ethConfiguration
            etl
            freeRtosCm4SysTick
            lifecycle
            startUp
            watchdogManager
            safeLifecycle
            safeMemory
            safeWatchdog
    PUBLIC bspInputManager bspOutputManager)

add_library(osHooks src/osHooks.cpp)

target_include_directories(osHooks PRIVATE include)

target_link_libraries(osHooks PRIVATE common freeRtosCm4SysTick)

set_target_properties(
    startUp
    PROPERTIES PROP_LINKER_SCRIPT
               "${CMAKE_CURRENT_SOURCE_DIR}/linkerscript/application.dld")
set_target_properties(
    startUp
    PROPERTIES LINK_DEPENDS
               "${CMAKE_CURRENT_SOURCE_DIR}/linkerscript/application.dld")
