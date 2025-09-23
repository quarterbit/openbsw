add_library(bspInterruptsImpl src/suspendResumeAllInterrupts.cpp)

target_include_directories(bspInterruptsImpl PUBLIC include /workspaces/openbsw/libs/bsp/bspInterrupts/include)