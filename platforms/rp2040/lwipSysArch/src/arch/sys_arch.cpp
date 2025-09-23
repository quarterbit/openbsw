// Copyright 2024 quarterbit

#include "arch/sys_arch.h"
#include "pico/critical_section.h"

// Minimal lwIP sys_arch implementation for RP2040
// This is a placeholder for future WiFi implementation

extern "C" {

// System initialization - called by lwIP
void sys_init(void)
{
    // No initialization needed for now
}

// Protect critical section - disable interrupts
sys_prot_t sys_arch_protect(void)
{
    uint32_t state = save_and_disable_interrupts();
    return state;
}

// Unprotect critical section - restore interrupts
void sys_arch_unprotect(sys_prot_t pval)
{
    restore_interrupts(pval);
}

// Create a new thread - not implemented
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
    // Return invalid thread handle
    return nullptr;
}

// Get current time in milliseconds
u32_t sys_now(void)
{
    // Return 0 for now - should be implemented with a timer
    return 0;
}

// Create a new mailbox - not implemented
err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
    return ERR_MEM;
}

// Post a message to mailbox - not implemented
void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
    // Do nothing
}

// Try to post a message to mailbox - not implemented
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
    return ERR_MEM;
}

// Fetch a message from mailbox - not implemented
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
    return SYS_ARCH_TIMEOUT;
}

// Try to fetch a message from mailbox - not implemented
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
    return SYS_ARCH_TIMEOUT;
}

// Free mailbox - not implemented
void sys_mbox_free(sys_mbox_t *mbox)
{
    // Do nothing
}

// Check if mailbox is valid - not implemented
int sys_mbox_valid(sys_mbox_t *mbox)
{
    return 0;
}

// Set mailbox invalid - not implemented
void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
    // Do nothing
}

// Create semaphore - not implemented
err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
    return ERR_MEM;
}

// Signal semaphore - not implemented
void sys_sem_signal(sys_sem_t *sem)
{
    // Do nothing
}

// Wait for semaphore - not implemented
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
    return SYS_ARCH_TIMEOUT;
}

// Try to wait for semaphore - not implemented
void sys_sem_free(sys_sem_t *sem)
{
    // Do nothing
}

// Check if semaphore is valid - not implemented
int sys_sem_valid(sys_sem_t *sem)
{
    return 0;
}

// Set semaphore invalid - not implemented
void sys_sem_set_invalid(sys_sem_t *sem)
{
    // Do nothing
}

// Create mutex - not implemented
err_t sys_mutex_new(sys_mutex_t *mutex)
{
    return ERR_MEM;
}

// Lock mutex - not implemented
void sys_mutex_lock(sys_mutex_t *mutex)
{
    // Do nothing
}

// Unlock mutex - not implemented
void sys_mutex_unlock(sys_mutex_t *mutex)
{
    // Do nothing
}

// Free mutex - not implemented
void sys_mutex_free(sys_mutex_t *mutex)
{
    // Do nothing
}

// Check if mutex is valid - not implemented
int sys_mutex_valid(sys_mutex_t *mutex)
{
    return 0;
}

// Set mutex invalid - not implemented
void sys_mutex_set_invalid(sys_mutex_t *mutex)
{
    // Do nothing
}

}