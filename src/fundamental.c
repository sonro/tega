#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "tega/fundamental.h"

static uint32_t growCapacity(uint32_t current, uint32_t minimum);

TFUN_ByteRes TFUN_ByteRes_new() {
    TFUN_ByteRes res;
    res.byte = 0;
    res.err = TERR_Res_success;
    return res;
}

TFUN_BSliceRes TFUN_BSliceRes_new() {
    TFUN_BSliceRes slice;
    slice.ptr = NULL;
    slice.len = 0;
    slice.err = TERR_Res_success;
    return slice;
}

TFUN_CharRes TFUN_CharRes_new() {
    TFUN_CharRes res;
    res.ch = 0;
    res.err = TERR_Res_success;
    return res;
}

TFUN_CStrRes TFUN_CStrRes_new() {
    TFUN_CStrRes res;
    res.ptr = NULL;
    res.len = 0;
    res.err = TERR_Res_success;
    return res;
}

TFUN_WCharRes TFUN_WCharRes_new() {
    TFUN_WCharRes res;
    res.ch = 0;
    res.err = TERR_Res_success;
    return res;
}

TFUN_WStrRes TFUN_WStrRes_new() {
    TFUN_WStrRes res;
    res.ptr = NULL;
    res.len = 0;
    res.err = TERR_Res_success;
    return res;
}

TFUN_Bytes TFUN_Bytes_new() {
    TFUN_Bytes bytes;
    bytes.ptr = NULL;
    bytes.len = 0;
    bytes.cap = 0;
    return bytes;
}

TERR_Res TFUN_Bytes_initWithCapacity(TFUN_Bytes *bytes, uint32_t cap) {
    if (bytes->ptr != NULL) {
        free(bytes->ptr);
    }
    if (cap == 0) {
        *bytes = TFUN_Bytes_new();
        return TERR_Res_success;
    }
    bytes->ptr = calloc(cap, sizeof(uint8_t));
    bytes->len = 0;
    bytes->cap = cap;
    return bytes->ptr != NULL ? TERR_Res_success : TERR_Res_out_of_memory;
}

void TFUN_Bytes_deinit(TFUN_Bytes *bytes) {
    if (bytes->ptr != NULL) {
        free(bytes->ptr);
    }
    *bytes = TFUN_Bytes_new();
}

void TFUN_Bytes_resetRetainCapacity(TFUN_Bytes *bytes) {
    bytes->len = 0;
}

TERR_Res TFUN_Bytes_ensureCapacity(TFUN_Bytes *bytes, uint32_t cap) {
    if (bytes->cap >= cap) {
        return TERR_Res_success;
    }
    cap = growCapacity(bytes->cap, cap);
    uint8_t *new_ptr = calloc(cap, sizeof(uint8_t));
    if (new_ptr == NULL) {
        return TERR_Res_out_of_memory;
    }
    if (bytes->ptr != NULL) {
        memcpy(new_ptr, bytes->ptr, bytes->len);
        free(bytes->ptr);
    }
    bytes->ptr = new_ptr;
    bytes->cap = cap;
    return TERR_Res_success;
}

TERR_Res TFUN_Bytes_append(TFUN_Bytes *bytes, uint8_t b) {
    TERR_Res res = TFUN_Bytes_ensureCapacity(bytes, bytes->len + 1);
    if (res != TERR_Res_success) {
        return res;
    }
    TFUN_Bytes_appendUnsafe(bytes, b);
    return TERR_Res_success;
}

void TFUN_Bytes_appendUnsafe(TFUN_Bytes *bytes, uint8_t b) {
    assert(bytes->ptr != NULL);
    assert(bytes->len < bytes->cap);
    bytes->ptr[bytes->len] = b;
    bytes->len += 1;
}

void TFUN_Bytes_appendSliceUnsafe(TFUN_Bytes *bytes, TFUN_BSlice slice) {
    uint32_t new_len = bytes->len + slice.len;
    assert(new_len <= bytes->cap);
    assert(bytes->ptr != NULL);
    memcpy(bytes->ptr + bytes->len, slice.ptr, slice.len);
    bytes->len = new_len;
}

TFUN_ByteRes TFUN_Bytes_get(const TFUN_Bytes *bytes, uint32_t index) {
    TFUN_ByteRes res = TFUN_ByteRes_new();
    if (index >= bytes->len) {
        res.err = TERR_Res_out_of_bounds;
    } else {
        assert(bytes->ptr != NULL);
        res.byte = bytes->ptr[index];
    }
    return res;
}

static uint32_t growCapacity(uint32_t current, uint32_t minimum) {
    uint32_t new = current;
    while (true) {
        new = TFUN_addSaturateTypeUnsigned(uint32_t, new, new / 2 + 8);
        if (new >= minimum) {
            return new;
        }
    }
}
