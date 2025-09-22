// Copyright 2025 Accenture.

#include "commonDebug.h"

extern "C"
{
#ifndef PLATFORM_SUPPORT_ETHERNET
// Stub implementations when Ethernet support is disabled
void enetRxIsr() {}
void enetTxIsr() {}
#endif

void ENET_TX_Buffer_IRQHandler() { enetTxIsr(); }

void ENET_RX_Buffer_IRQHandler() { enetRxIsr(); }

void ENET_PRE_IRQHandler()
{
    // call_enet_isr_Error();
}

} /* extern "C" */
