add_library(tsn)

target_include_directories(tsn
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_sources(tsn 
    PRIVATE
    src/TsnConfiguration.cpp
    src/timesync/TimeSync.cpp
    src/timesync/GptpClock.cpp
)

target_link_libraries(tsn PUBLIC common platform)