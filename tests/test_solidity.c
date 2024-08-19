#include <tega.h>

#include "tests.h"

typedef enum TestVision {
    TEST_vision_seeable = 0,
    TEST_vision_perma_visible = 1,
    TEST_vision_invisible = 2
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
        (TestSolidity){TEGA_solidity_floor, TEST_vision_seeable, true, true});

    TEST("window is seeable, transparent, obstructive");
    testBooleanChecks(
        (TestSolidity){TEGA_solidity_window, TEST_vision_seeable, true, false});

    TEST("portal is seeable, opaque, traversible");
    testBooleanChecks(
        (TestSolidity){TEGA_solidity_portal, TEST_vision_seeable, false, true});

    TEST("solid is seeable, opaque, obstructive");
    testBooleanChecks(
        (TestSolidity){TEGA_solidity_solid, TEST_vision_seeable, false, false});

    TEST("decor is perma visible, transparent, traversible");
    testBooleanChecks((TestSolidity){TEGA_solidity_decor,
                                     TEST_vision_perma_visible, true, true});

    TEST("prism is perma visible, transparent, obstructive");
    testBooleanChecks((TestSolidity){TEGA_solidity_prism,
                                     TEST_vision_perma_visible, true, false});

    TEST("stage is perma visible, opaque, traversible");
    testBooleanChecks((TestSolidity){TEGA_solidity_stage,
                                     TEST_vision_perma_visible, false, true});

    TEST("fixture is perma visible, opaque, obstructive");
    testBooleanChecks((TestSolidity){TEGA_solidity_fixture,
                                     TEST_vision_perma_visible, false, false});

    TEST("empty is invisible, transparent, traversible");
    testBooleanChecks(
        (TestSolidity){TEGA_solidity_empty, TEST_vision_invisible, true, true});

    TEST("void is invisible, transparent, obstructive");
    testBooleanChecks(
        (TestSolidity){TEGA_solidity_void, TEST_vision_invisible, true, false});

    TEST("distortion is invisible, opaque, traversible");
    testBooleanChecks((TestSolidity){TEGA_solidity_distortion,
                                     TEST_vision_invisible, false, true});

    TEST("dark matter is invisible, opaque, obstructive");
    testBooleanChecks((TestSolidity){TEGA_solidity_dark_matter,
                                     TEST_vision_invisible, false, false});
}

static void testBooleanChecks(const TestSolidity t) {
    testBooleanVisiblity(t.vision, t.solidity);

    EXPECT(TEGA_solidityIsTransparent(t.solidity) == t.transparent);
    EXPECT(TEGA_solidityIsOpaque(t.solidity) != t.transparent);

    EXPECT(TEGA_solidityIsTraversable(t.solidity) == t.traversible);
    EXPECT(TEGA_solidityIsObstructive(t.solidity) != t.traversible);
}

static void testBooleanVisiblity(const TestVision vision,
                                 const TEGA_Solidity s) {
    switch (vision) {
    case TEST_vision_seeable:
        EXPECT(TEGA_solidityIsSeeable(s));
        EXPECT(!TEGA_solidityIsPermaVisible(s));
        EXPECT(!TEGA_solidityIsInvisible(s));
        break;
    case TEST_vision_perma_visible:
        EXPECT(TEGA_solidityIsSeeable(s));
        EXPECT(TEGA_solidityIsPermaVisible(s));
        EXPECT(!TEGA_solidityIsInvisible(s));
        break;
    case TEST_vision_invisible:
        EXPECT(!TEGA_solidityIsSeeable(s));
        EXPECT(!TEGA_solidityIsPermaVisible(s));
        EXPECT(TEGA_solidityIsInvisible(s));
        break;
    }
}
