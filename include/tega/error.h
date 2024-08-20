/** ========================================================
 * TEGA Error
 *
 * Error handling and reporting.
 * ========================================================*/

#pragma once

#include <stdint.h>

// Int representation of `TEGA_Res` for efficient memory usage
typedef uint8_t TERR_ResInt;

/**
 * Operation Result
 *
 * 0 indicates success
 * > 0 indicates failure
 */
typedef enum TERR_Res {
    TERR_Res_success = 0,
    TERR_Res_failure = 1,
    TERR_Res_out_of_memory = 2,
} TERR_Res;
