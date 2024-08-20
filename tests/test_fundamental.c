#include "fundamental/test_fundamental.h"
#include "tests.h"

void testFundamental() {
    testTFUN_addSaturate();
    testTFUN_ResTypes();
    testTFUN_Bytes();
    testTFUN_BSlice();
    testTFUN_CString();
    testTFUN_CStrSlice();
    testTFUN_WString();
    testTFUN_WStrSlice();
}
