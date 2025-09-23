// Copyright 2024 quarterbit

#pragma once

#include <stdint.h>
#include <assert.h>

typedef unsigned char bool_t;
#ifndef FALSE
#define FALSE 0 /**< boolean 'false' value */
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define BYTE_ORDER LITTLE_ENDIAN

#define LWIP_CHKSUM_ALGORITHM 3

#define MEM_ALIGNMENT 4

#define PACK_STRUCT_STRUCT

/* Minimal logging for now */
#define LWIP_PLATFORM_DIAG(x) do { } while(0)

#define LWIP_PLATFORM_ASSERT(x) assert(x)

#define LWIP_NO_STDINT_H   0
#define LWIP_NO_INTTYPES_H 0

#define U16_F "u"
#define S16_F "d"
#define X8_F  "x"
#define X16_F "x"
#define U32_F "u"
#define S32_F "d"
#define X32_F "x"
#define SZT_F "u"

#ifndef CHECKSUM_CHECK_IP
#define CHECKSUM_CHECK_IP 1
#endif