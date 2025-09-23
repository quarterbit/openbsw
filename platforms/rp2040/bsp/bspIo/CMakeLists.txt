add_library(bspIo src/io/Io.cpp)

target_include_directories(bspIo PUBLIC include ../../../../libs/bsw/bsp/include)

target_link_libraries(bspIo PUBLIC bspMcu)

if (BUILD_UNIT_TESTS)
    # Unit tests not implemented yet
    # add_library(bspIoMock mock/gmock/io/ioMock.cpp)
    # target_include_directories(bspIoMock PUBLIC mock/include)
    # target_link_libraries(bspIoMock PRIVATE bspIo bspIoTest gmock_main)
endif ()