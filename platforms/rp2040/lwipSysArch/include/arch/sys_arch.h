// Copyright 2024 quarterbit

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef uint32_t sys_prot_t;

sys_prot_t sys_arch_protect(void);
void sys_arch_unprotect(sys_prot_t pval);

#ifdef __cplusplus
}
#endif