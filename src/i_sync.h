#pragma once

#include <pthread.h>

#include "tega/sync.h"

typedef struct I_TSYN_Threads {
    pthread_t input;
    pthread_t write;
    pthread_t world;
    pthread_t render;
} I_TSYN_Threads;

typedef struct I_TSYN_Channels {
    TSYN_MpscChannel log;
    TSYN_MpscChannel render;
    TSYN_PubSubChannel input;
    TSYN_PubSubChannel world;
    TSYN_PubSubChannel timing;
} I_TSYN_Channels;

typedef struct I_TSYN_State {
    I_TSYN_Threads threads;
    I_TSYN_Channels channels;
} I_TSYN_State;

void I_TSYN_init(const TSYN_Config config);
void I_TSYN_deinit();
