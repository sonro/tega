#include <tega/fundamental.h>

#include "../tests.h"
#include "test_fundamental.h"

static void addSaturate();
static void addSaturateUnsigned();
static void addSaturateTypeUnsigned();

void testTFUN_addSaturate() {
    addSaturate();
    addSaturateUnsigned();
    addSaturateTypeUnsigned();
}

static void addSaturate() {
    TEST("TFUN_addSaturate all 0");
    EXPECT(0 == TFUN_addSaturate(0, 0, 0, 0));

    TEST("TFUN_addSaturate all 1");
    EXPECT(1 == TFUN_addSaturate(1, 1, 1, 1));

    TEST("TFUN_addSaturate all -1");
    EXPECT(-1 == TFUN_addSaturate(-1, -1, -1, -1));

    TEST("TFUN_addSaturate min max 0, a b 1");
    EXPECT(0 == TFUN_addSaturate(0, 0, 1, 1));

    TEST("TFUN_addSaturate min max 0, a b -1");
    EXPECT(0 == TFUN_addSaturate(0, 0, -1, -1));

    TEST("TFUN_addSaturate min max 1, a b 0");
    EXPECT(0 == TFUN_addSaturate(1, 1, 0, 0));

    TEST("TFUN_addSaturate take min from 0");
    EXPECT(-5 == TFUN_addSaturate(-5, 0, 0, -5));

    TEST("TFUN_addSaturate add 1 to max");
    EXPECT(5 == TFUN_addSaturate(0, 5, 1, 5));
}

static void addSaturateUnsigned() {
    TEST("TFUN_addSaturateUnsigned all 0");
    EXPECT(0 == TFUN_addSaturateUnsigned(0, 0, 0));

    TEST("TFUN_addSaturateUnsigned all 1");
    EXPECT(1 == TFUN_addSaturateUnsigned(1, 1, 1));

    TEST("TFUN_addSaturateUnsigned negative");
    EXPECT(-2 == TFUN_addSaturateUnsigned(0, -1, -1));

    TEST("TFUN_addSaturateUnsigned add 1 to max");
    EXPECT(2 == TFUN_addSaturateUnsigned(2, 1, 2));
}

static void addSaturateTypeUnsigned() {
    TEST("TFUN_addSaturateTypeUnsigned u32 all 0");
    EXPECT(0 == TFUN_addSaturateTypeUnsigned(uint32_t, 0, 0));

    TEST("TFUN_addSaturateTypeUnsigned u32 both 1");
    EXPECT(2 == TFUN_addSaturateTypeUnsigned(uint32_t, 1, 1));

    TEST("TFUN_addSaturateTypeUnsigned u32 add 1 to max");
    EXPECT(UINT32_MAX == TFUN_addSaturateTypeUnsigned(uint32_t, 1, UINT32_MAX));

    TEST("TFUN_addSaturateTypeUnsigned u8 add 1 to max");
    EXPECT(UINT8_MAX == TFUN_addSaturateTypeUnsigned(uint8_t, 1, UINT8_MAX));
}
