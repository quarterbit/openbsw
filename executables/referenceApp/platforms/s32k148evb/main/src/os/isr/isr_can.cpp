// Copyright 2024 Accenture.

#include "commonDebug.h"

extern "C"
{
#ifndef PLATFORM_SUPPORT_CAN
// Stub implementations when CAN support is disabled
void call_can_isr_RX() {}
void call_can_isr_TX() {}
#endif

void CAN0_ORed_0_15_MB_IRQHandler() { call_can_isr_RX(); }

void CAN0_ORed_16_31_MB_IRQHandler() { call_can_isr_TX(); }

} /* extern "C" */
