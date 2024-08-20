#include <stdlib.h>

#include <tega/fundamental.h>

#include "../tests.h"
#include "test_fundamental.h"

static void bytesDeinit();
static void bytesNew();
static void bytesInitWithCapacity();
static void bytesResetRetainCapacity();
static void bytesEnsureCapacity();
static void bytesAppend();

void testTFUN_Bytes() {
    bytesDeinit();
    bytesNew();
    bytesInitWithCapacity();
    bytesResetRetainCapacity();
    bytesEnsureCapacity();
    bytesAppend();
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
    TFUN_Bytes bytes = TFUN_Bytes_new();
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
    uint8_t *old_ptr = bytes.ptr;
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

    free(bytes.ptr);
}

static void bytesEnsureCapacity() {
    TEST("TFUN_Bytes_ensureCapacity with 0 capacity");
    TFUN_Bytes bytes = TFUN_Bytes_new();
    TERR_Res res = TFUN_Bytes_ensureCapacity(&bytes, 0);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr == NULL);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 0);

    TEST("TFUN_Bytes_ensureCapacity existing cap 0 new cap 1");
    res = TFUN_Bytes_ensureCapacity(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr != NULL);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 8);

    TEST("TFUN_Bytes_ensureCapacity existing cap 8 new cap 0");
    uint8_t *old_ptr = bytes.ptr;
    res = TFUN_Bytes_ensureCapacity(&bytes, 0);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr == old_ptr);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 8);

    TEST("TFUN_Bytes_ensureCapacity existing cap 8 new cap 0 null ptr");
    // try to not get back the same pointer
    void *random_ptr = malloc(1);
    bytes.ptr = NULL;
    res = TFUN_Bytes_ensureCapacity(&bytes, 0);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr != old_ptr);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 8);

    free(old_ptr);
    free(random_ptr);

    TEST("TFUN_Bytes_ensureCapacity existing cap 8 new cap 8");
    old_ptr = bytes.ptr;
    random_ptr = malloc(1);
    res = TFUN_Bytes_ensureCapacity(&bytes, 8);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr == old_ptr);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 8);

    free(random_ptr);

    TEST("TFUN_Bytes_ensureCapacity existing cap 8 new cap 10");
    random_ptr = malloc(1);
    res = TFUN_Bytes_ensureCapacity(&bytes, 10);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr != old_ptr);
    EXPECT(bytes.len == 0);
    EXPECT(bytes.cap == 20);

    free(bytes.ptr);
    free(random_ptr);
}

static void bytesAppend() {
    TEST("TFUN_Bytes_append with 0 capacity");
    TFUN_Bytes bytes = TFUN_Bytes_new();
    TERR_Res res = TFUN_Bytes_append(&bytes, 0);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr != NULL);
    EXPECT(bytes.len == 1);
    EXPECT(bytes.cap == 8);

    TFUN_Bytes_deinit(&bytes);

    TEST("TFUN_Bytes_append with 1 capacity");
    bytes = TFUN_Bytes_new();
    bytes.cap = 1;
    bytes.ptr = calloc(1, sizeof(uint8_t));
    res = TFUN_Bytes_append(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr != NULL);
    EXPECT(bytes.len == 1);
    EXPECT(bytes.cap == 1);

    TFUN_Bytes_deinit(&bytes);

    TEST("TFUN_Bytes_append with full capacity");
    bytes = TFUN_Bytes_new();
    bytes.cap = 8;
    bytes.len = 8;
    res = TFUN_Bytes_append(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr != NULL);
    EXPECT(bytes.len == 9);
    EXPECT(bytes.cap == 20);

    TFUN_Bytes_deinit(&bytes);

    TEST("TFUN_Bytes_append empty then get");
    bytes = TFUN_Bytes_new();
    res = TFUN_Bytes_append(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    EXPECT(bytes.ptr != NULL);
    EXPECT(bytes.len == 1);
    EXPECT(bytes.cap == 8);
    EXPECT(bytes.ptr[0] == 1);
    TFUN_ByteRes byte_res = TFUN_Bytes_get(&bytes, 0);
    ASSERT(byte_res.err == TERR_Res_success);
    EXPECT(byte_res.byte == 1);

    TFUN_Bytes_deinit(&bytes);
}
