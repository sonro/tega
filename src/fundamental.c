#include <stdlib.h>
#include <string.h>

#include "tega/fundamental.h"

static uint32_t growCapacity(uint32_t current, uint32_t minimum);

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

static uint32_t growCapacity(uint32_t current, uint32_t minimum) {
    uint32_t new = current;
    while (true) {
        new = TFUN_addSaturateTypeUnsigned(uint32_t, new, new / 2 + 8);
        if (new >= minimum) {
            return new;
        }
    }
}
