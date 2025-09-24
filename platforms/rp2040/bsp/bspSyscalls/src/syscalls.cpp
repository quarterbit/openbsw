/**
 * \file syscalls.cpp
 * \brief Minimal syscall implementations for RP2040 embedded system
 * 
 * These are stub implementations of standard C library system calls
 * required by newlib for embedded systems. They provide minimal
 * functionality to satisfy the linker without external dependencies.
 */

#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

extern "C" {

/**
 * Exit a program without cleanup
 * In an embedded system, this typically triggers a system reset
 */
void _exit(int status) {
    // In a real embedded system, this might trigger a watchdog reset
    // or enter an infinite loop. For now, just loop forever.
    (void)status;
    while (1) {
        // Infinite loop - system should be reset externally
    }
}

/**
 * Close a file descriptor
 * Not implemented for embedded systems
 */
int _close(int file) {
    (void)file;
    errno = EBADF;
    return -1;
}

/**
 * Status of an open file
 * Not implemented for embedded systems
 */
int _fstat(int file, struct stat *st) {
    (void)file;
    if (st) {
        st->st_mode = S_IFCHR; // Character device
    }
    return 0;
}

/**
 * Query whether output stream is a terminal
 * In embedded systems, assume all file descriptors are terminals
 */
int _isatty(int file) {
    (void)file;
    return 1; // All file descriptors are "terminals" in embedded context
}

/**
 * Send a signal to a process
 * Not applicable in embedded systems
 */
int _kill(int pid, int sig) {
    (void)pid;
    (void)sig;
    errno = EINVAL;
    return -1;
}

/**
 * Get process ID
 * Not applicable in embedded systems
 */
int _getpid(void) {
    return 1; // Single process system
}

/**
 * Set position in a file
 * Not implemented for embedded systems
 */
int _lseek(int file, int ptr, int dir) {
    (void)file;
    (void)ptr;
    (void)dir;
    errno = ESPIPE;
    return -1;
}

/**
 * Read from a file
 * Could be implemented to read from UART or other input device
 */
int _read(int file, char *ptr, int len) {
    (void)file;
    (void)ptr;
    (void)len;
    // For now, no input is available
    errno = EAGAIN;
    return 0;
}

/**
 * Increase program data space (heap allocation)
 * Simple heap management for embedded systems
 */
extern char _end; // End of bss segment, defined by linker
static char *heap_ptr = &_end;

void* _sbrk(int incr) {
    char *prev_heap_ptr = heap_ptr;
    
    // Simple bounds check - you might want to define heap limits
    // For now, just assume we have enough memory
    heap_ptr += incr;
    
    return (void*)prev_heap_ptr;
}

/**
 * Write to a file descriptor
 * Could be implemented to write to UART or other output device
 */
int _write(int file, char *ptr, int len) {
    (void)file;
    // For now, just discard the output
    // In a real implementation, this could write to UART, USB CDC, etc.
    (void)ptr;
    return len; // Pretend we wrote everything
}

} // extern "C"