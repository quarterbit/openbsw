#ifndef PORTMACRO_H
#define PORTMACRO_H

// FreeRTOS portmacro.h for RP2040 (Cortex-M0+)

#include <stdint.h>
#include <stddef.h>

// Data types
#define portCHAR        char
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        long
#define portSHORT       short
#define portSTACK_TYPE  uint32_t
#define portBASE_TYPE   long

typedef portSTACK_TYPE StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
    typedef uint16_t TickType_t;
    #define portMAX_DELAY   ( TickType_t ) 0xffff
#else
    typedef uint32_t TickType_t;
    #define portMAX_DELAY   ( TickType_t ) 0xffffffffUL
#endif

// Critical section macros
#define portENTER_CRITICAL()    vPortEnterCritical()
#define portEXIT_CRITICAL()     vPortExitCritical()

// Task utilities
#define portYIELD()                         __asm volatile ( "svc 0" ::: "memory" )
#define portEND_SWITCHING_ISR(xSwitchRequired) portYIELD_FROM_ISR(xSwitchRequired)
#define portYIELD_FROM_ISR(x)               do { if(x) portYIELD(); } while(0)

// Tickless idle
#define portSUPPRESS_TICKS_AND_SLEEP(xExpectedIdleTime) // Not implemented yet

// Task function macros
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters) void vFunction(void *pvParameters)
#define portTASK_FUNCTION(vFunction, pvParameters) void vFunction(void *pvParameters)

// Architecture specifics
#define portBYTE_ALIGNMENT      8
#define portSTACK_GROWTH        (-1)
#define portTICK_PERIOD_MS      ((TickType_t) 1000 / configTICK_RATE_HZ)
#define portNOP()               __asm volatile ("nop")

// Function declarations
void vPortEnterCritical(void);
void vPortExitCritical(void);
BaseType_t xPortStartScheduler(void);
void vPortEndScheduler(void);

#endif /* PORTMACRO_H */