#include <stdlib.h>

#include "tega/fundamental.h"

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
    bytes->ptr = malloc(cap);
    bytes->len = 0;
    bytes->cap = cap;
    return TERR_Res_success;
}

void TFUN_Bytes_free(TFUN_Bytes *bytes) {
    if (bytes->ptr != NULL) {
        free(bytes->ptr);
    }
    *bytes = TFUN_Bytes_new();
}
