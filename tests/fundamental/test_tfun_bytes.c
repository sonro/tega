#include <stdlib.h>

#include <tega/fundamental.h>

#include "../tests.h"
#include "test_fundamental.h"

static void bytesDeinit();
static void bytesNew();
static void bytesInitWithCapacity();
static void bytesResetRetainCapacity();
static void bytesEnsureCapacity();
static void bytesGet();
static void bytesAppend();
static void bytesAppendUnsafe();

void testTFUN_Bytes() {
    bytesDeinit();
    bytesNew();
    bytesInitWithCapacity();
    bytesResetRetainCapacity();
    bytesEnsureCapacity();
    bytesGet();
    bytesAppend();
    bytesAppendUnsafe();
}

static void bytesDeinit() {
    TEST("TFUN_Bytes_deinit with a NULL pointer");
    TFUN_Bytes bytes = {.ptr = NULL, .len = 0, .cap = 0};
    TFUN_Bytes_deinit(&bytes);
    EXPECT(bytes.ptr == NULL);

    TEST("TFUN_Bytes_deinit resets capacity and len to 0");
    bytes.cap = 1;
    bytes.len = 1;
    TFUN_Bytes_deinit(&bytes);
    TEST_ArrayList(0, 0, 0, bytes);
}

static void bytesNew() {
    TEST("TFUN_Bytes_new");
    TFUN_Bytes bytes = TFUN_Bytes_new();
    TEST_ArrayList(0, 0, 0, bytes);
}

static void bytesInitWithCapacity() {
    TEST("TFUN_Bytes_initWithCapacity 0 does not allocate");
    TFUN_Bytes bytes = TFUN_Bytes_new();
    TERR_Res res = TFUN_Bytes_initWithCapacity(&bytes, 0);
    TEST_ArrayList(0, 0, 0, bytes);

    TEST("TFUN_Bytes_initWithCapacity 1 allocates 1 byte");
    res = TFUN_Bytes_initWithCapacity(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList_notNull(0, 1, bytes);

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
    TEST_ArrayList(0, 0, 0, bytes);

    TEST("TFUN_Bytes_resetRetainCapacity with capacity");
    bytes.cap = 1;
    TFUN_Bytes_resetRetainCapacity(&bytes);
    TEST_ArrayList(0, 0, 1, bytes);

    TEST("TFUN_Bytes_resetRetainCapacity with data");
    bytes.ptr = calloc(1, sizeof(uint8_t));
    bytes.len = 1;
    const uint8_t *old_ptr = bytes.ptr;
    TFUN_Bytes_resetRetainCapacity(&bytes);
    TEST_ArrayList(old_ptr, 0, 1, bytes);

    free(bytes.ptr);
}

static void bytesEnsureCapacity() {
    TEST("TFUN_Bytes_ensureCapacity with 0 capacity");
    TFUN_Bytes bytes = TFUN_Bytes_new();
    TERR_Res res = TFUN_Bytes_ensureCapacity(&bytes, 0);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList(0, 0, 0, bytes);

    TEST("TFUN_Bytes_ensureCapacity existing cap 0 new cap 1");
    res = TFUN_Bytes_ensureCapacity(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList_notNull(0, 8, bytes);

    TEST("TFUN_Bytes_ensureCapacity existing cap 8 new cap 0");
    uint8_t *old_ptr = bytes.ptr;
    res = TFUN_Bytes_ensureCapacity(&bytes, 0);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList(old_ptr, 0, 8, bytes);

    TEST("TFUN_Bytes_ensureCapacity existing cap 8 new cap 0 null ptr");
    // try to not get back the same pointer
    void *random_ptr = malloc(1);
    bytes.ptr = NULL;
    res = TFUN_Bytes_ensureCapacity(&bytes, 0);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList_notPtr(old_ptr, 0, 8, bytes);

    free(old_ptr);
    free(random_ptr);

    TEST("TFUN_Bytes_ensureCapacity existing cap 8 new cap 8");
    old_ptr = bytes.ptr;
    random_ptr = malloc(1);
    res = TFUN_Bytes_ensureCapacity(&bytes, 8);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList(old_ptr, 0, 8, bytes);

    free(random_ptr);

    TEST("TFUN_Bytes_ensureCapacity existing cap 8 new cap 10");
    random_ptr = malloc(1);
    res = TFUN_Bytes_ensureCapacity(&bytes, 10);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList_notPtr(old_ptr, 0, 20, bytes);

    free(bytes.ptr);
    free(random_ptr);
}

static void bytesGet() {
    TEST("TFUN_Bytes_get with 0 len is out of bounds");
    TFUN_Bytes bytes = TFUN_Bytes_new();
    TFUN_ByteRes res = TFUN_Bytes_get(&bytes, 0);
    EXPECT(res.err == TERR_Res_out_of_bounds);

    TEST("TFUN_Bytes_get with 1 len");
    uint8_t buf[1] = {3};
    bytes.ptr = buf;
    bytes.len = 1;
    bytes.cap = 1;
    res = TFUN_Bytes_get(&bytes, 0);
    TEST_ByteRes(3, res);

    TEST("TFUN_Bytes_get with 2 len");
    uint8_t buf_2[2] = {3, 5};
    bytes.ptr = buf_2;
    bytes.len = 2;
    bytes.cap = 2;
    res = TFUN_Bytes_get(&bytes, 1);
    TEST_ByteRes(5, res);
}

static void bytesAppend() {
    TEST("TFUN_Bytes_append with 0 capacity");
    TFUN_Bytes bytes = TFUN_Bytes_new();
    TERR_Res res = TFUN_Bytes_append(&bytes, 0);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList_notNull(1, 8, bytes);

    TFUN_Bytes_deinit(&bytes);

    TEST("TFUN_Bytes_append with 1 capacity");
    bytes = TFUN_Bytes_new();
    bytes.cap = 1;
    bytes.ptr = calloc(1, sizeof(uint8_t));
    res = TFUN_Bytes_append(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList_notNull(1, 1, bytes);

    TFUN_Bytes_deinit(&bytes);

    TEST("TFUN_Bytes_append with full capacity");
    bytes = TFUN_Bytes_new();
    bytes.cap = 8;
    bytes.len = 8;
    res = TFUN_Bytes_append(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList_notNull(9, 20, bytes);

    TFUN_Bytes_deinit(&bytes);

    TEST("TFUN_Bytes_append empty then get");
    bytes = TFUN_Bytes_new();
    res = TFUN_Bytes_append(&bytes, 1);
    ASSERT(res == TERR_Res_success);
    TEST_ArrayList_notNull(1, 8, bytes);
    EXPECT(bytes.ptr[0] == 1);
    TFUN_ByteRes byte_res = TFUN_Bytes_get(&bytes, 0);
    TEST_ByteRes(1, byte_res);

    TFUN_Bytes_deinit(&bytes);
}

static void bytesAppendUnsafe() {
    TEST("TFUN_Bytes_appendUnsafe");
    uint8_t buf[1] = {0};
    TFUN_Bytes bytes = {.ptr = buf, .len = 0, .cap = 1};
    TFUN_Bytes_appendUnsafe(&bytes, 5);
    TEST_ArrayList(buf, 1, 1, bytes);
    EXPECT(bytes.ptr[0] == 5);
}
