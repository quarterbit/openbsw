
# Consider dependencies only in project.
set(CMAKE_DEPENDS_IN_PROJECT_ONLY OFF)

# The set of languages for which implicit dependencies are needed:
set(CMAKE_DEPENDS_LANGUAGES
  "ASM"
  )
# The set of files for implicit dependencies of each language:
set(CMAKE_DEPENDS_CHECK_ASM
  "/workspaces/openbsw/executables/referenceApp/platforms/s32k148evb/main/src/bsp/bootHeader.S" "/workspaces/openbsw/executables/referenceApp/build-arm/platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/bsp/bootHeader.S.obj"
  "/workspaces/openbsw/executables/referenceApp/platforms/s32k148evb/main/src/bsp/startUp.S" "/workspaces/openbsw/executables/referenceApp/build-arm/platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/bsp/startUp.S.obj"
  )
set(CMAKE_ASM_COMPILER_ID "GNU")

# Preprocessor definitions for this target.
set(CMAKE_TARGET_DEFINITIONS_ASM
  "ESTL_NO_ASSERT_MESSAGE=1"
  "PLATFORM_SUPPORT_IO=1"
  "PLATFORM_SUPPORT_MPU=1"
  "PLATFORM_SUPPORT_WATCHDOG=1"
  "REALTIME_OS=1"
  )

# The include file search paths:
set(CMAKE_ASM_TARGET_INCLUDE_PATH
  "/workspaces/openbsw/platforms/s32k1xx/bsp/bspMcu/include"
  "/workspaces/openbsw/libs/bsw/platform/include"
  "/workspaces/openbsw/libs/bsw/common/include"
  "/workspaces/openbsw/libs/3rdparty/etl/include"
  "/workspaces/openbsw/libs/3rdparty/etl_configuration"
  "/workspaces/openbsw/libs/3rdparty/etl_addons/include"
  )

# The set of dependency files which are needed:
set(CMAKE_DEPENDS_DEPENDENCY_FILES
  "/workspaces/openbsw/executables/referenceApp/platforms/s32k148evb/main/src/os/isr/isr_can.cpp" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_can.cpp.obj" "gcc" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_can.cpp.obj.d"
  "/workspaces/openbsw/executables/referenceApp/platforms/s32k148evb/main/src/os/isr/isr_enet.cpp" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_enet.cpp.obj" "gcc" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_enet.cpp.obj.d"
  "/workspaces/openbsw/executables/referenceApp/platforms/s32k148evb/main/src/os/isr/isr_erm.cpp" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_erm.cpp.obj" "gcc" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_erm.cpp.obj.d"
  "/workspaces/openbsw/executables/referenceApp/platforms/s32k148evb/main/src/os/isr/isr_ftfc.cpp" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_ftfc.cpp.obj" "gcc" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_ftfc.cpp.obj.d"
  "/workspaces/openbsw/executables/referenceApp/platforms/s32k148evb/main/src/os/isr/isr_sys.cpp" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_sys.cpp.obj" "gcc" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_sys.cpp.obj.d"
  "/workspaces/openbsw/executables/referenceApp/platforms/s32k148evb/main/src/os/isr/isr_wdg.cpp" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_wdg.cpp.obj" "gcc" "platforms/s32k148evb/main/CMakeFiles/startUp.dir/src/os/isr/isr_wdg.cpp.obj.d"
  )

# Targets to which this target links which contain Fortran sources.
set(CMAKE_Fortran_TARGET_LINKED_INFO_FILES
  )

# Targets to which this target links which contain Fortran sources.
set(CMAKE_Fortran_TARGET_FORWARD_LINKED_INFO_FILES
  )

# Fortran module output directory.
set(CMAKE_Fortran_TARGET_MODULE_DIR "")
