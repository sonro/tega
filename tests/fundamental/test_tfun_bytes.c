#include <tega/fundamental.h>

#include "../tests.h"
#include "test_fundamental.h"

static void bytesFree();
static void bytesNew();
static void bytesInitWithCapacity();

void testTFUN_Bytes() {
    bytesFree();
    bytesNew();
    bytesInitWithCapacity();
}

static void bytesFree() {
    TEST("TFUN_Bytes_free with a NULL pointer");
    TFUN_Bytes bytes = (TFUN_Bytes){.ptr = NULL, .len = 0, .cap = 0};
    TFUN_Bytes_free(&bytes);
    EXPECT(bytes.ptr == NULL);

    TEST("TFUN_Bytes_free resets capacity and len to 0");
    bytes.cap = 1;
    bytes.len = 1;
    TFUN_Bytes_free(&bytes);
    EXPECT(bytes.cap == 0);
    EXPECT(bytes.len == 0);
}

static void bytesNew() {
    TEST("TFUN_Bytes_new");
    TFUN_Bytes bytes = TFUN_Bytes_new();
    EXPECT(bytes.ptr == NULL);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 0);
}

static void bytesInitWithCapacity() {
    TEST("TFUN_Bytes_newWithCapacity 0 does not allocate");
    TFUN_Bytes bytes;
    TERR_Res res = TFUN_Bytes_initWithCapacity(&bytes, 0);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr == NULL);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 0);

    TEST("TFUN_Bytes_newWithCapacity 1 allocates 1 byte");
    res = TFUN_Bytes_initWithCapacity(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr != NULL);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 1);

    TFUN_Bytes_free(&bytes);
}
