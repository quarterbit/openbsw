add_library(hcsr04 STATIC)

target_sources(hcsr04 PRIVATE
    hcsr04.cpp
)

target_include_directories(hcsr04 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(hcsr04 PRIVATE
    bsp
)

# Only link bspIo for non-POSIX platforms (S32K1xx has GPIO, POSIX doesn't)
if(NOT BUILD_TARGET_PLATFORM STREQUAL "POSIX")
    target_link_libraries(hcsr04 PRIVATE bspIo)
endif()