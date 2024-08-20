#pragma once

typedef struct failure {
    const char *assertion;
    const char *file;
    const int line;
} Failure;

[[noreturn]]
void failExit(const Failure failure);
void fail(const Failure failure);
void success();
void setTest(char *test);

#define TEST(name) setTest(name)
#define _CREATE_FAILURE(name)                                                  \
    (Failure) {                                                                \
        .assertion = name, .file = __FILE__, .line = __LINE__                  \
    }
#define EXPECT(ast)                                                            \
    if (ast) {                                                                 \
        success();                                                             \
    } else {                                                                   \
        const Failure failure = _CREATE_FAILURE(#ast);                         \
        fail(failure);                                                         \
    }
#define ASSERT(ast)                                                            \
    if (ast) {                                                                 \
        success();                                                             \
    } else {                                                                   \
        const Failure failure = _CREATE_FAILURE(#ast);                         \
        failExit(failure);                                                     \
    }

/** TEST FILES **/
void testSolidity();
void testFundamental();

static inline void runTests() {
    testSolidity();
    testFundamental();
}
