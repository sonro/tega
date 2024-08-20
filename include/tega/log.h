#pragma once

typedef enum TLOG_Level {
    TLOG_Level_trace = 0,
    TLOG_Level_debug = 1,
    TLOG_Level_info = 2,
    TLOG_Level_warn = 3,
    TLOG_Level_error = 4,
    TLOG_Level_fatal = 5,
} TLOG_Level;

typedef struct TLOG_Logger {
    const char *name;
} TLOG_Logger;

void TLOG_log(const TLOG_Logger *logger, TLOG_Level level, const char *format,
              ...);

#define TLOG_trace_enabled

#ifdef TLOG_trace_enabled
#define TLOG_trace(__logger, ...)                                              \
    TLOG_log(__logger, TLOG_Level_trace, __VA_ARGS__)
#endif
