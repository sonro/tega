#include <tega.h>

#include "tests.h"

typedef enum TestVision {
    TestVision_seeable = 0,
    TestVision_perma_visible = 1,
    TestVision_invisible = 2
} TestVision;

typedef struct TestSolidity {
    TEGA_Solidity solidity;
    TestVision vision;
    bool transparent;
    bool traversible;
} TestSolidity;

static void booleanChecks();
static void testBooleanChecks(const TestSolidity t);
static void testBooleanVisiblity(const TestVision vision,
                                 const TEGA_Solidity s);
void testSolidity() {
    booleanChecks();
}

static void booleanChecks() {
    TEST("floor is seeable, transparent, traversible");
    testBooleanChecks(
        (TestSolidity){TEGA_Solidity_floor, TestVision_seeable, true, true});

    TEST("window is seeable, transparent, obstructive");
    testBooleanChecks(
        (TestSolidity){TEGA_Solidity_window, TestVision_seeable, true, false});

    TEST("portal is seeable, opaque, traversible");
    testBooleanChecks(
        (TestSolidity){TEGA_Solidity_portal, TestVision_seeable, false, true});

    TEST("solid is seeable, opaque, obstructive");
    testBooleanChecks(
        (TestSolidity){TEGA_Solidity_solid, TestVision_seeable, false, false});

    TEST("decor is perma visible, transparent, traversible");
    testBooleanChecks((TestSolidity){TEGA_Solidity_decor,
                                     TestVision_perma_visible, true, true});

    TEST("prism is perma visible, transparent, obstructive");
    testBooleanChecks((TestSolidity){TEGA_Solidity_prism,
                                     TestVision_perma_visible, true, false});

    TEST("stage is perma visible, opaque, traversible");
    testBooleanChecks((TestSolidity){TEGA_Solidity_stage,
                                     TestVision_perma_visible, false, true});

    TEST("fixture is perma visible, opaque, obstructive");
    testBooleanChecks((TestSolidity){TEGA_Solidity_fixture,
                                     TestVision_perma_visible, false, false});

    TEST("empty is invisible, transparent, traversible");
    testBooleanChecks(
        (TestSolidity){TEGA_Solidity_empty, TestVision_invisible, true, true});

    TEST("void is invisible, transparent, obstructive");
    testBooleanChecks(
        (TestSolidity){TEGA_Solidity_void, TestVision_invisible, true, false});

    TEST("distortion is invisible, opaque, traversible");
    testBooleanChecks((TestSolidity){TEGA_Solidity_distortion,
                                     TestVision_invisible, false, true});

    TEST("dark matter is invisible, opaque, obstructive");
    testBooleanChecks((TestSolidity){TEGA_Solidity_dark_matter,
                                     TestVision_invisible, false, false});
}

static void testBooleanChecks(const TestSolidity t) {
    testBooleanVisiblity(t.vision, t.solidity);

    EXPECT(TEGA_Solidity_isTransparent(t.solidity) == t.transparent);
    EXPECT(TEGA_Solidity_isOpaque(t.solidity) != t.transparent);

    EXPECT(TEGA_Solidity_isTraversable(t.solidity) == t.traversible);
    EXPECT(TEGA_Solidity_isObstructive(t.solidity) != t.traversible);
}

static void testBooleanVisiblity(const TestVision vision,
                                 const TEGA_Solidity s) {
    switch (vision) {
    case TestVision_seeable:
        EXPECT(TEGA_Solidity_isSeeable(s));
        EXPECT(!TEGA_Solidity_isPermaVisible(s));
        EXPECT(!TEGA_Solidity_isInvisible(s));
        break;
    case TestVision_perma_visible:
        EXPECT(TEGA_Solidity_isSeeable(s));
        EXPECT(TEGA_Solidity_isPermaVisible(s));
        EXPECT(!TEGA_Solidity_isInvisible(s));
        break;
    case TestVision_invisible:
        EXPECT(!TEGA_Solidity_isSeeable(s));
        EXPECT(!TEGA_Solidity_isPermaVisible(s));
        EXPECT(TEGA_Solidity_isInvisible(s));
        break;
    }
}
