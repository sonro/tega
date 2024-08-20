#include <tega/error.h>

#include "tests.h"

void testError() {
    TEST("TERR_Res success and failure values");
    TERR_Res success = TERR_Res_success;
    TERR_Res failure = TERR_Res_failure;
    EXPECT(success == 0);
    ASSERT(failure > 0);
}
