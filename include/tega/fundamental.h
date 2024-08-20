/** ========================================================
 * TEGA Fundamental
 *
 * For memory management, string operations, etc.
 * ========================================================*/

#pragma once

#include <stdint.h>
#include <wchar.h>

#include "tega/error.h"

#define TFUN_addSaturateUnsigned(_max, _a, _b)                                 \
    ({                                                                         \
        __typeof__(_a) __a = (_a);                                             \
        __typeof__(_b) __b = (_b);                                             \
        __typeof__(_max) __max = (_max);                                       \
        (__a > __max - __b) ? __max : (__a + __b);                             \
    })

#define TFUN_addSaturate(_min, _max, _a, _b)                                   \
    ({                                                                         \
        __typeof__(_a) __a = (_a);                                             \
        __typeof__(_b) __b = (_b);                                             \
        __typeof__(_min) __min = (_min);                                       \
        __typeof__(_max) __max = (_max);                                       \
        __typeof__(_a + _b) __result = __a + __b;                              \
        (__b > 0 && __a > __max - __b)   ? __max                               \
        : (__b < 0 && __a < __min - __b) ? __min                               \
                                         : __result;                           \
    })

#define TFUN_addSaturateTypeUnsigned(_type, _a, _b)                            \
    ({                                                                         \
        _type _max = (_type)~0;                                                \
        TFUN_addSaturateUnsigned(_max, (_a), (_b));                            \
    })

// Growable byte array
typedef struct TFUN_Bytes {
    uint8_t *ptr;
    uint32_t len;
    uint32_t cap;
} TFUN_Bytes;

// Immutable view of a `TFUN_Bytes`
typedef struct TFUN_BSlice {
    const uint8_t *ptr;
    uint32_t len;
} TFUN_BSlice;

TFUN_Bytes TFUN_Bytes_new();

/**
 * - If `cap` is 0 there will be no allocation
 * - If `bytes` was previously initialized it will be reset
 */
TERR_Res TFUN_Bytes_initWithCapacity(TFUN_Bytes *bytes, uint32_t cap);
void TFUN_Bytes_deinit(TFUN_Bytes *bytes);
void TFUN_Bytes_resetRetainCapacity(TFUN_Bytes *bytes);
TERR_Res TFUN_Bytes_ensureCapacity(TFUN_Bytes *bytes, uint32_t cap);
TERR_Res TFUN_Bytes_append(TFUN_Bytes *bytes, uint8_t byte);
void TFUN_Bytes_appendUnsafe(TFUN_Bytes *bytes, uint8_t byte);
TERR_Res TFUN_Bytes_appendSlice(TFUN_Bytes *bytes, const TFUN_BSlice slice);
void TFUN_Bytes_appendSliceUnsafe(TFUN_Bytes *bytes, const TFUN_BSlice slice);
uint8_t TFUN_Bytes_get(TFUN_Bytes *const bytes, uint32_t index);
TFUN_BSlice TFUN_Bytes_slice(TFUN_Bytes *const bytes, uint32_t start,
                             uint32_t end);

/**
 * Growable standard C string
 *
 * No wide characters support
 */
typedef struct TFUN_CString {
    char *ptr;
    uint32_t len;
    uint32_t cap;
} TFUN_CString;

// Immutable view of a `TFUN_CString`
typedef struct TFUN_CStrSlice {
    const char *ptr;
    uint32_t len;
} TFUN_CStrSlice;

TFUN_CString TFUN_CString_new();

/**
 * - If `cap` is 0 there will be no allocation
 * - If `string` was previously initialized it will be reset
 */
TERR_Res TFUN_CString_initWithCapacity(TFUN_CString *string, uint32_t cap);
void TFUN_CString_deinit(TFUN_CString *string);
void TFUN_CString_resetRetainCapacity(TFUN_CString *string);
TERR_Res TFUN_CString_ensureCapacity(TFUN_CString *string, uint32_t cap);
TERR_Res TFUN_CString_append(TFUN_CString *string, char ch);
void TFUN_CString_appendUnsafe(TFUN_CString *string, char ch);
TERR_Res TFUN_CString_appendSlice(TFUN_CString *string,
                                  const TFUN_CStrSlice slice);
void TFUN_CString_appendSliceUnsafe(TFUN_CString *string,
                                    const TFUN_CStrSlice slice);
char TFUN_CString_get(TFUN_CString *const string, uint32_t index);
TFUN_CStrSlice TFUN_CString_slice(TFUN_CString *const string, uint32_t start,
                                  uint32_t end);
TFUN_BSlice TFUN_CString_bSlice(TFUN_CString *const string, uint32_t start,
                                uint32_t end);
// Zero copy but `string` will no longer be valid after this call
TFUN_Bytes TFUN_CString_toBytes(TFUN_CString *string);

// Growable string of wide characters
typedef struct TFUN_WString {
    wchar_t *ptr;
    uint32_t len;
    uint32_t cap;
} TFUN_WString;

// Immutable view of a `TFUN_WString`
typedef struct TFUN_WStrSlice {
    const wchar_t *ptr;
    uint32_t len;
} TFUN_WStrSlice;

TFUN_WString TFUN_WString_new();

/**
 * - If `cap` is 0 there will be no allocation
 * - If `string` was previously initialized it will be reset
 */
TERR_Res TFUN_WString_initWithCapacity(TFUN_WString *string, uint32_t cap);
void TFUN_WString_deinit(TFUN_WString *string);
void TFUN_WString_resetRetainCapacity(TFUN_WString *string);
TERR_Res TFUN_WString_ensureCapacity(TFUN_WString *string, uint32_t cap);
TERR_Res TFUN_WString_append(TFUN_WString *string, wchar_t ch);
void TFUN_WString_appendUnsafe(TFUN_WString *string, wchar_t ch);
TERR_Res TFUN_WString_appendSlice(TFUN_WString *string,
                                  const TFUN_WStrSlice slice);
void TFUN_WString_appendSliceUnsafe(TFUN_WString *string,
                                    const TFUN_WStrSlice slice);
wchar_t TFUN_WString_get(TFUN_WString *const string, uint32_t index);
TFUN_WStrSlice TFUN_WString_slice(TFUN_WString *const string, uint32_t start,
                                  uint32_t end);
TFUN_BSlice TFUN_WString_bSlice(TFUN_WString *const string, uint32_t start,
                                uint32_t end);
// Zero copy but `string` will no longer be valid after this call
TFUN_Bytes TFUN_WString_toBytes(TFUN_WString *string);
