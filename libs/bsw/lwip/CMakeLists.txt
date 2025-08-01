add_library(lwip)

target_include_directories(lwip
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_sources(lwip 
    PRIVATE
    src/LwipInterface.cpp
)

target_link_libraries(lwip PUBLIC common platform)