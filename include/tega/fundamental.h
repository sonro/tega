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

// Byte when `err` is `TERR_Res_success`
typedef struct TFUN_ByteRes {
    uint8_t byte;
    TERR_ResInt err;
} TFUN_ByteRes;

// `TFUN_BSlice` when `err` is `TERR_Res_success`
typedef struct TFUN_BSliceRes {
    const uint8_t *ptr;
    uint32_t len;
    TERR_Res err;
} TFUN_BSliceRes;

// `TERR_Res_success` and `byte` = 0
TFUN_ByteRes TFUN_ByteRes_new();

// `TERR_Res_success`, `ptr` = `NULL` and `len` = 0
TFUN_BSliceRes TFUN_BSliceRes_new();

// Empty `TFUN_Bytes` without allocating
TFUN_Bytes TFUN_Bytes_new();

/**
 * Empty `TFUN_Bytes` with at exactly `cap` capacity
 *
 * - If `cap` is 0 there will be no allocation
 * - If `bytes` was previously initialized it will be freed
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_Bytes_initWithCapacity(TFUN_Bytes *bytes, uint32_t cap);

// Frees memory and resets to a new empty `TFUN_Bytes`
void TFUN_Bytes_deinit(TFUN_Bytes *bytes);

// Empties the array list while keeping the allocated memory
void TFUN_Bytes_resetRetainCapacity(TFUN_Bytes *bytes);

/**
 * Makes sure `bytes` has at least `cap` capacity
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_Bytes_ensureCapacity(TFUN_Bytes *bytes, uint32_t cap);

/**
 * Pushes a `byte` onto `bytes` array list
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_Bytes_append(TFUN_Bytes *bytes, uint8_t byte);

/**
 * Pushes a `byte` onto `bytes` array list
 *
 * Safety:
 * - assumes `bytes` can hold `byte`
 */
void TFUN_Bytes_appendUnsafe(TFUN_Bytes *bytes, uint8_t byte);

/**
 * Pushes a `slice` onto `bytes` array list
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_Bytes_appendSlice(TFUN_Bytes *bytes, const TFUN_BSlice slice);

/**
 * Pushes a `slice` onto `bytes` array list
 *
 * Safety:
 * - assumes `bytes` can hold `slice`
 */
void TFUN_Bytes_appendSliceUnsafe(TFUN_Bytes *bytes, const TFUN_BSlice slice);

/**
 * Get a single byte
 *
 * Errors:
 * - `index` is out of bounds
 */
TFUN_ByteRes TFUN_Bytes_get(const TFUN_Bytes *bytes, uint32_t index);

/**
 * Get a single byte
 *
 * Safety:
 * - assumes `index` is in bounds
 */
uint8_t TFUN_Bytes_getUnsafe(const TFUN_Bytes *bytes, uint32_t index);

/**
 * Get a slice of bytes from `start` up to and not including `end`
 *
 * Errors:
 * - `start` is out of bounds
 * - `end` is out of bounds
 * - `end` < `start`: invalid range
 */
TFUN_BSliceRes TFUN_Bytes_slice(const TFUN_Bytes *bytes, uint32_t start,
                                uint32_t end);

/**
 * Get a slice of bytes from `start` up to and not including `end`
 *
 * Safety:
 * - assumes `start` and `end` are in bounds
 * - assumes range is valid
 */
TFUN_BSlice TFUN_Bytes_sliceUnsafe(const TFUN_Bytes *bytes, uint32_t start,
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

// Char when `err` is `TERR_Res_success`
typedef struct TFUN_CharRes {
    char ch;
    TERR_ResInt err;
} TFUN_CharRes;

// `TFUN_CStrSlice` when `err` is `TERR_Res_success`
typedef struct TFUN_CStrRes {
    const char *ptr;
    uint32_t len;
    TERR_Res err;
} TFUN_CStrRes;

// `TERR_Res_success` and `char` = 0
TFUN_CharRes TFUN_CharRes_new();

// `TERR_Res_success`, `ptr` = `NULL`, `len` = 0
TFUN_CStrRes TFUN_CStrRes_new();

// Empty `TFUN_CString` without allocating
TFUN_CString TFUN_CString_new();

/**
 * Empty `TFUN_CString` with at exactly `cap` capacity
 *
 * - If `cap` is 0 there will be no allocation
 * - If `string` was previously initialized it will be reset
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_CString_initWithCapacity(TFUN_CString *string, uint32_t cap);

// Frees memory and resets to a new empty `TFUN_CString`
void TFUN_CString_deinit(TFUN_CString *string);

// Empties the `string` while keeping the allocated memory
void TFUN_CString_resetRetainCapacity(TFUN_CString *string);

/**
 * Makes sure `string` has at least `cap` capacity
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_CString_ensureCapacity(TFUN_CString *string, uint32_t cap);

/**
 * Pushes a `char` onto `string`
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_CString_append(TFUN_CString *string, char ch);

/**
 * Pushes a `char` onto `string`
 *
 * Safety:
 * - assumes `string` can hold `ch`
 */
void TFUN_CString_appendUnsafe(TFUN_CString *string, char ch);

/**
 * Pushes a `slice` onto `string`
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_CString_appendSlice(TFUN_CString *string,
                                  const TFUN_CStrSlice slice);

/**
 * Pushes a `slice` onto `string`
 *
 * Safety:
 * - assumes `string` can hold `slice`
 */
void TFUN_CString_appendSliceUnsafe(TFUN_CString *string,
                                    const TFUN_CStrSlice slice);

/**
 * Get a single char
 *
 * Errors:
 * - `index` is out of bounds
 */
TFUN_CharRes TFUN_CString_get(const TFUN_CString *string, uint32_t index);

/**
 * Get a single char
 *
 * Safety:
 * - assumes `index` is in bounds
 */
char TFUN_CString_getUnsafe(const TFUN_CString *string, uint32_t index);

/**
 * Get a slice of chars from `start` up to and not including `end`
 *
 * Errors:
 * - `start` is out of bounds
 * - `end` is out of bounds
 * - `end` < `start`: invalid range
 */
TFUN_CStrRes TFUN_CString_slice(const TFUN_CString *string, uint32_t start,
                                uint32_t end);
/**
 * Get a slice of chars from `start` up to and not including `end`
 *
 * Safety:
 * - assumes `start` and `end` are in bounds
 * - assumes range is valid
 */
TFUN_CStrSlice TFUN_CString_sliceUnsafe(const TFUN_CString *string,
                                        uint32_t start, uint32_t end);

/**
 * Get a `TFUN_BSlice` from `start` up to and not including `end`
 *
 * Errors:
 * - `start` is out of bounds
 * - `end` is out of bounds
 * - `end` < `start`: invalid range
 */
TFUN_BSliceRes TFUN_CString_bSlice(const TFUN_CString *string, uint32_t start,
                                   uint32_t end);

/**
 * Get a `TFUN_BSlice` from `start` up to and not including `end`
 *
 * Safety:
 * - assumes `start` and `end` are in bounds
 * - assumes range is valid
 */
TFUN_BSlice TFUN_CString_bSliceUnsafe(const TFUN_CString *string,
                                      uint32_t start, uint32_t end);

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

// Wide char when `err` is `TERR_Res_success`
typedef struct TFUN_WCharRes {
    wchar_t ch;
    TERR_Res err;
} TFUN_WCharRes;

// `TFUN_WStrSlice` when `err` is `TERR_Res_success`
typedef struct TFUN_WStrRes {
    const wchar_t *ptr;
    uint32_t len;
    TERR_Res err;
} TFUN_WStrRes;

// `TERR_Res_success` and `ch` = 0
TFUN_WCharRes TFUN_WCharRes_new();

// `TERR_Res_success`, `ptr` = `NULL` and `len` = 0
TFUN_WStrRes TFUN_WStrRes_new();

// Empty `TFUN_WString` without allocating
TFUN_WString TFUN_WString_new();

/**
 * Empty `TFUN_WString` with at exactly `cap` capacity
 *
 * - If `cap` is 0 there will be no allocation
 * - If `string` was previously initialized it will be freed
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_WString_initWithCapacity(TFUN_WString *string, uint32_t cap);

// Frees memory and resets to a new empty `TFUN_WString`
void TFUN_WString_deinit(TFUN_WString *string);

// Empties the `string` while keeping the allocated memory
void TFUN_WString_resetRetainCapacity(TFUN_WString *string);

/**
 * Ensures that `string` has at least `cap` capacity
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_WString_ensureCapacity(TFUN_WString *string, uint32_t cap);

/**
 * Appends `ch` to `string`
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_WString_append(TFUN_WString *string, wchar_t ch);

/**
 * Appends `ch` to `string`
 *
 * Safety:
 * - assumes `string` can hold `ch`
 */
void TFUN_WString_appendUnsafe(TFUN_WString *string, wchar_t ch);

/**
 * Appends `slice` to `string`
 *
 * Errors:
 * - out of memory
 */
TERR_Res TFUN_WString_appendSlice(TFUN_WString *string,
                                  const TFUN_WStrSlice slice);

/**
 * Appends `slice` to `string`
 *
 * Safety:
 * - assumes `string` can hold `slice`
 */
void TFUN_WString_appendSliceUnsafe(TFUN_WString *string,
                                    const TFUN_WStrSlice slice);

/**
 * Get a single wide character
 *
 * Errors:
 * - `index` is out of bounds
 */
TFUN_WCharRes TFUN_WString_get(const TFUN_WString *string, uint32_t index);

/**
 * Get a single wide character
 *
 * Safety:
 * - assumes `index` is in bounds
 */
wchar_t TFUN_WString_getUnsafe(const TFUN_WString *string, uint32_t index);

/**
 * Get a `TFUN_WStrSlice` from `start` up to and not including `end`
 *
 * Errors:
 * - `end` is out of bounds
 * - `end` < `start`: invalid range
 */
TFUN_WStrRes TFUN_WString_slice(const TFUN_WString *string, uint32_t start,
                                uint32_t end);

/**
 * Get a `TFUN_WStrSlice` from `start` up to and not including `end`
 *
 * Safety:
 * - assumes `start` and `end` are in bounds
 * - assumes range is valid
 */
TFUN_WStrSlice TFUN_WString_sliceUnsafe(const TFUN_WString *string,
                                        uint32_t start, uint32_t end);

/**
 * Get a `TFUN_BSlice` from `start` up to and not including `end`
 *
 * Errors:
 * - `end` is out of bounds
 * - `end` < `start`: invalid range
 */
TFUN_BSliceRes TFUN_WString_bSlice(const TFUN_WString *string, uint32_t start,
                                   uint32_t end);

/**
 * Get a `TFUN_BSlice` from `start` up to and not including `end`
 *
 * Safety:
 * - assumes `start` and `end` are in bounds
 * - assumes range is valid
 */
TFUN_BSlice TFUN_WString_bSliceUnsafe(const TFUN_WString *string,
                                      uint32_t start, uint32_t end);

// Zero copy but `string` will no longer be valid after this call
TFUN_Bytes TFUN_WString_toBytes(TFUN_WString *string);
