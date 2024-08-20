#include <tega/fundamental.h>

#include "../tests.h"
#include "test_fundamental.h"

static void byteResNew();
static void bSliceResNew();
static void charResNew();
static void cStrResNew();
static void wCharResNew();
static void wStrResNew();

void testTFUN_ResTypes() {
    byteResNew();
    bSliceResNew();
    charResNew();
    cStrResNew();
    wCharResNew();
    wStrResNew();
}

static void byteResNew() {
    TEST("TFUN_ByteRes_new");
    TFUN_ByteRes res = TFUN_ByteRes_new();
    EXPECT(res.byte == 0);
    EXPECT(res.err == TERR_Res_success);
}

static void bSliceResNew() {
    TEST("TFUN_BSliceRes_new");
    TFUN_BSliceRes res = TFUN_BSliceRes_new();
    EXPECT(res.ptr == NULL);
    EXPECT(res.len == 0);
    EXPECT(res.err == TERR_Res_success);
}

static void charResNew() {
    TEST("TFUN_CharRes_new");
    TFUN_CharRes res = TFUN_CharRes_new();
    EXPECT(res.ch == 0);
    EXPECT(res.err == TERR_Res_success);
}

static void cStrResNew() {
    TEST("TFUN_CStrRes_new");
    TFUN_CStrRes res = TFUN_CStrRes_new();
    EXPECT(res.ptr == NULL);
    EXPECT(res.len == 0);
    EXPECT(res.err == TERR_Res_success);
}

static void wCharResNew() {
    TEST("TFUN_WCharRes_new");
    TFUN_WCharRes res = TFUN_WCharRes_new();
    EXPECT(res.ch == 0);
    EXPECT(res.err == TERR_Res_success);
}

static void wStrResNew() {
    TEST("TFUN_WStrRes_new");
    TFUN_WStrRes res = TFUN_WStrRes_new();
    EXPECT(res.ptr == NULL);
    EXPECT(res.len == 0);
    EXPECT(res.err == TERR_Res_success);
}
