#pragma once

typedef struct failure {
    const char *assertion;
    const char *file;
    const int line;
} Failure;

[[noreturn]]
void failExit(const Failure failure);

void fail(const Failure failure);

void setTest(char *test);

#define TEST(name) setTest(name)
#define EXPECT(ast)                                                            \
    if (ast) {                                                                 \
        putchar('.');                                                          \
    } else {                                                                   \
        putchar('F');                                                          \
        const Failure failure =                                                \
            (Failure){.assertion = #ast, .file = __FILE__, .line = __LINE__};  \
        fail(failure);                                                         \
    }
#define ASSERT(ast)                                                            \
    if (ast) {                                                                 \
        putchar('.');                                                          \
    } else {                                                                   \
        const Failure failure =                                                \
            (Failure){.assertion = #ast, .file = __FILE__, .line = __LINE__};  \
        failExit(failure);                                                     \
    }

static inline void runTests() {}
