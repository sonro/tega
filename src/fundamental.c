#include "tega/fundamental.h"

TFUN_Bytes TFUN_Bytes_new() {
    TFUN_Bytes bytes;
    bytes.ptr = NULL;
    bytes.len = 0;
    bytes.cap = 0;
    return bytes;
}
