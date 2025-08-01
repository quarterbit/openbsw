add_library(ethernet)

target_include_directories(ethernet
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_sources(ethernet 
    PRIVATE
    src/EthernetTransportLayer.cpp
    src/TsnEthernetTransportLayer.cpp
)

target_link_libraries(ethernet PUBLIC transport lwip tsn)