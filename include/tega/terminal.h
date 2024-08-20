/** ========================================================
 * TEGA Terminal
 *
 * Used by the engine to draw and manage the terminal
 * ========================================================*/

#pragma once

#include <stdint.h>

// Position within the terminal screen
typedef struct TERM_TermPos {
    int32_t x;
    int32_t y;
} TERM_TermPos;

// Position within a window
typedef struct TERM_WinPos {
    int32_t x;
    int32_t y;
} TERM_WinPos;
