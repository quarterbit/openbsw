// Copyright 2024 Accenture.
// RP2040 specific FreeRTOS hook functions

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

extern "C"
{
void vApplicationStackOverflowHook(TaskHandle_t /* xTask */, char* /* pcTaskName */)
{
    printf("vApplicationStackOverflowHook\r\n");
}

void vIllegalISR()
{
    printf("vIllegalISR\r\n");
    for (;;)
        ;
}

// RP2040 specific hooks (if needed)
void vApplicationMallocFailedHook(void)
{
    printf("vApplicationMallocFailedHook\r\n");
    for (;;)
        ;
}

void vApplicationIdleHook(void)
{
    // Idle hook for RP2040 - can be used for low power mode
}
}