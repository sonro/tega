#pragma once

typedef struct failure {
    const char *assertion;
    const char *file;
    const int line;
} Failure;

[[noreturn]]
void __failExit(const Failure failure);
void __fail(const Failure failure);
void __success();
void __setTest(char *test);

#define TEST(__name) __setTest(__name)
#define _CREATE_FAILURE(__name)                                                \
    (Failure) {                                                                \
        .assertion = __name, .file = __FILE__, .line = __LINE__                \
    }
#define EXPECT(ast)                                                            \
    if (ast) {                                                                 \
        __success();                                                           \
    } else {                                                                   \
        const Failure __failure = _CREATE_FAILURE(#ast);                       \
        __fail(__failure);                                                     \
    }
#define ASSERT(ast)                                                            \
    if (ast) {                                                                 \
        __success();                                                           \
    } else {                                                                   \
        const Failure __failure = _CREATE_FAILURE(#ast);                       \
        __failExit(__failure);                                                 \
    }

/** TEST FILES **/
void testSolidity();
void testFundamental();
void testError();

static inline void runTests() {
    testSolidity();
    testFundamental();
    testError();
}
