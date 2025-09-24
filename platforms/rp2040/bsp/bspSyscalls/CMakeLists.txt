add_library(bspSyscalls STATIC
    src/syscalls.cpp
)

target_include_directories(bspSyscalls
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# No external dependencies - completely standalone
target_compile_features(bspSyscalls PRIVATE cxx_std_14)