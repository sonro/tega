#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tests.h"

#define PRINT_RED "\033[0;31m"
#define PRINT_GREEN "\033[0;32m"
#define PRINT_RESET "\033[0m"

static char *test_name = "";
static int pass_count = 0;
static int fail_count = 0;
static int fail_capacity = 0;
static const char **failures = NULL;

[[noreturn]]
static void finish();
static void printSummary();
static char *formatFailure(const Failure failure);
static void failureAppend(const char *str);
static void cleanup();

int main() {
    printf("Running tests:\n\n");
    runTests();
    finish();
}

void __setTest(char *test) {
    test_name = test;
}

void __success() {
    pass_count++;
    putchar('.');
}

void __fail(const Failure failure) {
    printf("%sF%s", PRINT_RED, PRINT_RESET);
    const char *fail_str = formatFailure(failure);
    failureAppend(fail_str);
}

[[noreturn]]
void __failExit(const Failure failure) {
    __fail(failure);
    finish();
}

[[noreturn]]
static void finish() {
    printSummary();
    cleanup();
    exit(fail_count);
}

static char *formatFailure(const Failure failure) {
    const char *filename = basename((char *)failure.file);
    char buf[1024] = {0};
    snprintf(buf, 1024, "%s%s:%d%s\n    %s: %s\n", PRINT_RED, filename,
             failure.line, PRINT_RESET, test_name, failure.assertion);
    size_t len = strlen(buf);
    char *fail_str = calloc(len + 1, sizeof(char));
    if (fail_str == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(-1);
    }
    memcpy(fail_str, buf, len);
    return fail_str;
}

static void failureAppend(const char *str) {
    if (fail_count == fail_capacity) {
        if (fail_capacity == 0) {
            fail_capacity = 8;
            failures = malloc(fail_capacity * sizeof(char *));
        } else {
            fail_capacity *= 2;
            failures = realloc(failures, fail_capacity * sizeof(char *));
        }
        if (failures == NULL) {
            fprintf(stderr, "Out of memory\n");
            exit(-1);
        }
    }
    failures[fail_count++] = str;
}

static void printSummary() {
    printf("\n\n");
    if (fail_count > 0) {
        printf("Failures:\n");
        for (int i = 0; i < fail_count; i++) {
            printf("    %s\n", failures[i]);
        }
    }
    printf("Summary:\n");
    printf("    Tests passed: %s%d\n%s", PRINT_GREEN, pass_count, PRINT_RESET);
    printf("    Tests failed: %s%d\n%s",
           fail_count > 0 ? PRINT_RED : PRINT_GREEN, fail_count, PRINT_RESET);
}

static void cleanup() {
    for (int i = 0; i < fail_count; i++) {
        free((void *)failures[i]);
    }
    free(failures);
}
