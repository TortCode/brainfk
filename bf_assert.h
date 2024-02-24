#include <assert.h>
#include <stdio.h>

#define assert_msg(msg, expr)             \
    if (!expr) {                          \
        printf("Failed: %s\n", (msg));    \
        printf("  file: %s\n", __FILE__); \
        printf("  line: %d\n", __LINE__); \
        printf("  expr: %s\n", (# expr)); \
    }