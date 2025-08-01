add_executable(tsnTest src/TsnConfigurationTest.cpp)

target_link_libraries(tsnTest PRIVATE tsn gmock_main)

gtest_discover_tests(tsnTest PROPERTIES LABELS "tsnTest")