#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tega/log.h"

#define MSG_SIZE 1024

typedef struct LogMessage {
    char *msg;
} LogMessage;

static TLOG_Level global_level = TLOG_Level_trace;

static thread_local char local_msg[MSG_SIZE] = {0};

static void sendLocalMessage();

void TLOG_log(const TLOG_Logger *logger, TLOG_Level level, const char *format,
              ...) {
    (void)logger;
    (void)format;
    (void)local_msg;

    if (level < global_level) {
        return;
    }

    sendLocalMessage();
}

static void sendLocalMessage() {}
