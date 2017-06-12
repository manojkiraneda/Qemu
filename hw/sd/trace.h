/* This file is autogenerated by tracetool, do not edit. */

#ifndef TRACE_HW_SD_GENERATED_TRACERS_H
#define TRACE_HW_SD_GENERATED_TRACERS_H

#include "qemu-common.h"
#include "trace/control.h"

extern TraceEvent _TRACE_MILKYMIST_MEMCARD_MEMORY_READ_EVENT;
extern TraceEvent _TRACE_MILKYMIST_MEMCARD_MEMORY_WRITE_EVENT;
extern uint16_t _TRACE_MILKYMIST_MEMCARD_MEMORY_READ_DSTATE;
extern uint16_t _TRACE_MILKYMIST_MEMCARD_MEMORY_WRITE_DSTATE;
#define TRACE_MILKYMIST_MEMCARD_MEMORY_READ_ENABLED 1
#define TRACE_MILKYMIST_MEMCARD_MEMORY_WRITE_ENABLED 1
#include "qemu/log.h"


static inline void trace_milkymist_memcard_memory_read(uint32_t addr, uint32_t value)
{
    if (true) {
        if (trace_event_get_state(TRACE_MILKYMIST_MEMCARD_MEMORY_READ)) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
            qemu_log_mask(LOG_TRACE, "%d@%zd.%06zd:milkymist_memcard_memory_read " "addr %08x value %08x" "\n",
                          getpid(),
                          (size_t)_now.tv_sec, (size_t)_now.tv_usec
                          , addr, value);
        }
    }
}

static inline void trace_milkymist_memcard_memory_write(uint32_t addr, uint32_t value)
{
    if (true) {
        if (trace_event_get_state(TRACE_MILKYMIST_MEMCARD_MEMORY_WRITE)) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
            qemu_log_mask(LOG_TRACE, "%d@%zd.%06zd:milkymist_memcard_memory_write " "addr %08x value %08x" "\n",
                          getpid(),
                          (size_t)_now.tv_sec, (size_t)_now.tv_usec
                          , addr, value);
        }
    }
}
#endif /* TRACE_HW_SD_GENERATED_TRACERS_H */
