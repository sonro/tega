/** =======================================================
 * TEGA Sync
 *
 * For multithreading synchronization and communication
 * ========================================================*/

#pragma once

#include <stdint.h>

typedef struct TSYN_Config {
    uint16_t cores;
} TSYN_Config;

typedef struct TSYN_MpscChannel {
} TSYN_MpscChannel;

typedef struct TSYN_PubSubChannel {
} TSYN_PubSubChannel;
