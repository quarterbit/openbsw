# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/workspaces/openbsw/platforms/rp2040/3rdparty/pico-sdk/tools/pioasm"
  "/workspaces/openbsw/executables/referenceApp/build-rp2040/pioasm"
  "/workspaces/openbsw/executables/referenceApp/build-rp2040/pioasm-install"
  "/workspaces/openbsw/executables/referenceApp/build-rp2040/openbsw/platforms/rp2040/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/workspaces/openbsw/executables/referenceApp/build-rp2040/openbsw/platforms/rp2040/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
  "/workspaces/openbsw/executables/referenceApp/build-rp2040/openbsw/platforms/rp2040/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/workspaces/openbsw/executables/referenceApp/build-rp2040/openbsw/platforms/rp2040/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/workspaces/openbsw/executables/referenceApp/build-rp2040/openbsw/platforms/rp2040/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/workspaces/openbsw/executables/referenceApp/build-rp2040/openbsw/platforms/rp2040/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
