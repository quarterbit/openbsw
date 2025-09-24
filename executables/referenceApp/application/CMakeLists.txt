set(app.referenceAppExtraSources)

if (PLATFORM_SUPPORT_UDS)
    list(
        APPEND
        app.referenceAppExtraSources
        src/systems/TransportSystem.cpp
        src/systems/UdsSystem.cpp
        src/uds/ReadIdentifierPot.cpp)

    if (PLATFORM_SUPPORT_CAN)
        list(APPEND app.referenceAppExtraSources src/systems/DoCanSystem.cpp)
        list(APPEND app.referenceAppExtraSources src/app/CanDemoListener.cpp)
    endif ()
    if (PLATFORM_SUPPORT_ETHERNET)
        list(APPEND app.referenceAppExtraSources src/systems/EthernetSystem.cpp)
    endif ()
endif ()

if (PLATFORM_SUPPORT_STORAGE)
    list(APPEND app.referenceAppExtraSources src/systems/StorageSystem.cpp)
endif ()

add_executable(
    app.referenceApp
    src/app/app.cpp
    src/logger/logger.cpp
    src/console/console.cpp
    src/systems/LedProximitySystem.cpp
    src/systems/RuntimeSystem.cpp
    src/systems/SysAdminSystem.cpp
    src/systems/SafetySystem.cpp
    ${app.referenceAppExtraSources}
     src/main.cpp)

# Remove the incorrect LED proximity demo line since we added it above
# target_sources(app.referenceApp PRIVATE led_proximity.cpp)

set_target_properties(app.referenceApp PROPERTIES SUFFIX ".elf")

if (TARGET startUp)
    get_target_property(LINKER_SCRIPT startUp PROP_LINKER_SCRIPT)

    if (DEFINED LINKER_SCRIPT)
        target_link_options(app.referenceApp PRIVATE -T ${LINKER_SCRIPT})
    endif ()
endif ()

target_include_directories(app.referenceApp PRIVATE include)

target_link_libraries(
    app.referenceApp
    PRIVATE asyncBinding
            asyncConsole
            bspMcu
            configuration
            etl
            hcsr04
            lifecycle
            consoleCommands
            logger
            printf
            loggerIntegration
            main
            stdioConsoleInput
            osFreeRtos
            asyncFreeRtosImpl
            util
            udsConfigurationImpl
            runtime
            safeLifecycle
            socBsp
            ws2812b)

# Only link ethConfiguration if ethernet is supported
if (PLATFORM_SUPPORT_ETHERNET)
    target_link_libraries(app.referenceApp PRIVATE ethConfiguration)
endif()

# Only link ethConfiguration if ethernet is supported
if (PLATFORM_SUPPORT_ETHERNET)
    target_link_libraries(app.referenceApp PRIVATE ethConfiguration)
endif()

if (PLATFORM_SUPPORT_UDS)

    target_link_libraries(app.referenceApp PRIVATE transport
                                                   transportRouterSimple uds)

endif ()

if (PLATFORM_SUPPORT_CAN)

    target_link_libraries(app.referenceApp PRIVATE cpp2can docan)
endif ()

if (PLATFORM_SUPPORT_ETHERNET)

    target_link_libraries(app.referenceApp PRIVATE cpp2ethernet lwipSocket lwipcore)
endif ()

if (PLATFORM_SUPPORT_STORAGE)
    target_link_libraries(app.referenceApp PRIVATE storage)
endif ()
