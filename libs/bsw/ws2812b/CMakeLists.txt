add_library(ws2812b STATIC)

target_sources(ws2812b PRIVATE
    ws2812b.cpp
)

target_include_directories(ws2812b PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ws2812b PRIVATE
    bsp
)

# Only link bspIo for non-POSIX platforms (S32K1xx has GPIO, POSIX doesn't)
if(NOT BUILD_TARGET_PLATFORM STREQUAL "POSIX")
    target_link_libraries(ws2812b PRIVATE bspIo)
endif()