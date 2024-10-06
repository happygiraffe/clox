#ifndef clox_common_h
#define clox_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* When defined, print chunks. */
#define DEBUG_PRINT_CODE
/* When defined, print each instruction prior to execution. */
#define DEBUG_TRACE_EXECUTION

/* When defined, stress test the garbage collector. */
#define DEBUG_STRESS_GC

/* When defined, log detailed garbage collector output. */
#define DEBUG_LOG_GC

#define UINT8_COUNT (UINT8_MAX + 1)

#endif
