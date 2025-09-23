include_guard(GLOBAL)

include("${CMAKE_CURRENT_LIST_DIR}/ArmNoneEabi-header.cmake")

# RP2040 specific flags for Cortex-M0+
set(_ARCH_FLAGS "-mcpu=cortex-m0plus -mfloat-abi=soft")

set(_C_FLAGS "-funsigned-bitfields")

set(_CXX_FLAGS "-femit-class-debug-always \
    -funsigned-bitfields")

if(NOT _EXE_LINKER_FLAGS MATCHES "nano")
    set(_EXE_LINKER_FLAGS "-specs=nano.specs \
        -specs=nosys.specs")
endif()

# Set Pico SDK path for this toolchain
set(PICO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/platforms/rp2040/3rdparty/pico-sdk")

# Include Pico SDK
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(CMAKE_LINKER arm-none-eabi-g++)
set(CMAKE_AR arm-none-eabi-ar)

# Initialize Pico SDK after compilers are set
pico_sdk_init()