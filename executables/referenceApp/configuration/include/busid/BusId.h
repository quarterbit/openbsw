// Copyright 2024 Accenture.

#pragma once

#include "common/busid/BusId.h"

#include <cstdint>

namespace busid
{
static constexpr uint8_t SELFDIAG   = 1;
static constexpr uint8_t CAN_0      = 2;
static constexpr uint8_t ETHERNET_0 = 3;
static constexpr uint8_t LAST_BUS   = ETHERNET_0;

} // namespace busid
