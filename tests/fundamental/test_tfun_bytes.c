#include <stdlib.h>

#include <tega/fundamental.h>

#include "../tests.h"
#include "test_fundamental.h"

static void bytesDeinit();
static void bytesNew();
static void bytesInitWithCapacity();
static void bytesResetRetainCapacity();

void testTFUN_Bytes() {
    bytesDeinit();
    bytesNew();
    bytesInitWithCapacity();
    bytesResetRetainCapacity();
}

static void bytesDeinit() {
    TEST("TFUN_Bytes_deinit with a NULL pointer");
    TFUN_Bytes bytes = (TFUN_Bytes){.ptr = NULL, .len = 0, .cap = 0};
    TFUN_Bytes_deinit(&bytes);
    EXPECT(bytes.ptr == NULL);

    TEST("TFUN_Bytes_deinit resets capacity and len to 0");
    bytes.cap = 1;
    bytes.len = 1;
    TFUN_Bytes_deinit(&bytes);
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
    TEST("TFUN_Bytes_initWithCapacity 0 does not allocate");
    TFUN_Bytes bytes;
    TERR_Res res = TFUN_Bytes_initWithCapacity(&bytes, 0);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr == NULL);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 0);

    TEST("TFUN_Bytes_initWithCapacity 1 allocates 1 byte");
    res = TFUN_Bytes_initWithCapacity(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr != NULL);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 1);

    TEST("TFUN_Bytes_initWithCapacity re-allocates");
    // try to not get back the same pointer
    void *random_ptr = malloc(1);
    const uint8_t *old_ptr = bytes.ptr;
    res = TFUN_Bytes_initWithCapacity(&bytes, 2);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr != old_ptr);

    free(bytes.ptr);
    free(random_ptr);
}

static void bytesResetRetainCapacity() {
    TEST("TFUN_Bytes_resetRetainCapacity with 0 capacity");
    TFUN_Bytes bytes = TFUN_Bytes_new();
    TFUN_Bytes_resetRetainCapacity(&bytes);
    EXPECT(bytes.ptr == NULL);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 0);

    TEST("TFUN_Bytes_resetRetainCapacity with capacity");
    bytes.cap = 1;
    TFUN_Bytes_resetRetainCapacity(&bytes);
    EXPECT(bytes.ptr == NULL);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 1);

    TEST("TFUN_Bytes_resetRetainCapacity with data");
    bytes.ptr = calloc(1, sizeof(uint8_t));
    bytes.len = 1;
    const uint8_t *old_ptr = bytes.ptr;
    TFUN_Bytes_resetRetainCapacity(&bytes);
    EXPECT(bytes.ptr == old_ptr);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 1);
}
