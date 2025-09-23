// Copyright 2024 quarterbit

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

[[noreturn]] extern void softwareSystemReset(void);
extern void softwareDestructiveReset(void);

#ifdef __cplusplus
} // extern "C"
#endif