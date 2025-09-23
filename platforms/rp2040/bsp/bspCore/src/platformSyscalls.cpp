/**
 * RP2040 Newlib Syscalls Implementation
 * Minimal system call implementations for embedded use
 */

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdint>

extern "C" {

// Simple heap management
extern char _end[];  // Defined by linker
static char* heap_end = nullptr;

/**
 * Exit program - just halt in embedded systems
 */
void _exit(int status) {
    (void)status;
    while(1) {
        // Infinite loop - embedded systems don't exit
    }
}

/**
 * Write to file descriptor
 * Only supports stdout (fd=1) and stderr (fd=2)
 */
int _write(int fd, const void* buf, size_t count) {
    if (fd == 1 || fd == 2) { // stdout or stderr
        const char* data = static_cast<const char*>(buf);
        for (size_t i = 0; i < count; i++) {
            // Use our platform-specific putByteToStdout
            extern void putByteToStdout(int data);
            putByteToStdout(data[i]);
        }
        return count;
    }
    errno = EBADF;
    return -1;
}

/**
 * Increase heap size for malloc
 */
void* _sbrk(ptrdiff_t incr) {
    if (heap_end == nullptr) {
        heap_end = _end;
    }
    
    char* prev_heap_end = heap_end;
    heap_end += incr;
    
    return prev_heap_end;
}

/**
 * Kill process - not supported in embedded
 */
int _kill(int pid, int sig) {
    (void)pid;
    (void)sig;
    errno = EINVAL;
    return -1;
}

/**
 * Get process ID - always return 1 in embedded
 */
int _getpid(void) {
    return 1;
}

/**
 * Get file status - not supported
 */
int _fstat(int fd, struct stat* st) {
    (void)fd;
    if (st) {
        st->st_mode = S_IFCHR;
    }
    return 0;
}

/**
 * Check if file descriptor is a terminal
 */
int _isatty(int fd) {
    if (fd == 0 || fd == 1 || fd == 2) { // stdin, stdout, stderr
        return 1;
    }
    return 0;
}

/**
 * Close file - not supported
 */
int _close(int fd) {
    (void)fd;
    return -1;
}

/**
 * Read from file descriptor
 * Only supports stdin (fd=0)
 */
int _read(int fd, void* buf, size_t count) {
    if (fd == 0) { // stdin
        char* data = static_cast<char*>(buf);
        for (size_t i = 0; i < count; i++) {
            extern int getByteFromStdin(void);
            int byte = getByteFromStdin();
            if (byte == -1) {
                return i; // Return number of bytes read so far
            }
            data[i] = static_cast<char>(byte);
        }
        return count;
    }
    errno = EBADF;
    return -1;
}

/**
 * Seek in file - not supported
 */
off_t _lseek(int fd, off_t offset, int whence) {
    (void)fd;
    (void)offset;
    (void)whence;
    errno = ESPIPE;
    return -1;
}

} // extern "C"