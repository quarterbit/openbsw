# RP2040-specific GCC toolchain configuration override
# Resolves specs file conflicts for RP2040 platform

include_guard(GLOBAL)

# Override the standard ARM GCC configuration to fix specs file conflicts
include("${CMAKE_CURRENT_LIST_DIR}/../../../admin/cmake/ArmNoneEabi-header.cmake")

set(_C_FLAGS "-funsigned-bitfields")

set(_CXX_FLAGS "-femit-class-debug-always \
    -funsigned-bitfields")

# For RP2040, use only the specs that don't conflict
# Remove nano.specs and nosys.specs to avoid "nano_link" conflict
set(_EXE_LINKER_FLAGS "")

include("${CMAKE_CURRENT_LIST_DIR}/../../../admin/cmake/ArmNoneEabi.cmake")

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(CMAKE_LINKER arm-none-eabi-g++)
set(CMAKE_AR arm-none-eabi-ar)