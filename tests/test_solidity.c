#include <tega.h>

#include "tests.h"

static void boolean_checks_floor() {
    TEST("floor is seeable");
    ASSERT(true);

    TEST("floor is transparent");

    TEST("floor is traversible");
}

static void boolean_checks() {
    boolean_checks_floor();
}

void testSolidity() {
    boolean_checks();
}
