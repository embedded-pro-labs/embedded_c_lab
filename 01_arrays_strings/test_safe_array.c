/**
 * @file test_safe_array.c
 * @brief Systematic unit testing suite for safe_array operations.
 * @note Adheres to high-reliability software testing practices.
 * @author Embedded Pro Labs
 */

#include <stdio.h>
#include <stdbool.h>
#include "safe_array.h"

/* Simple test metrics */
static uint32_t tests_run = 0;
static uint32_t tests_passed = 0;

#define RUN_TEST(test_func) do { \
    printf("[ RUN     ] " #test_func "\n"); \
    tests_run++; \
    if (test_func()) { \
        printf("[  PASSED ] " #test_func "\n"); \
        tests_passed++; \
    } else { \
        printf("[  FAILED ] " #test_func "\n"); \
    } \
} while(0)

/* Test Case 1: Valid Copy (Happy Path) */
static bool test_valid_copy(void) {
    int32_t src[5] = {10, 20, 30, 40, 50};
    int32_t dest[5] = {0};
    
    safe_array_status_t status = safe_array_copy(dest, 5, src, 5, 1, 3);
    
    /* Verify success status */
    if (status != SAFE_ARRAY_SUCCESS) return false;
    
    /* Verify copied elements (offset 1, len 3 -> 20, 30, 40) */
    if (dest[0] != 20 || dest[1] != 30 || dest[2] != 40) return false;
    
    return true;
}

/* Test Case 2: Null Pointer Protection */
static bool test_null_pointers(void) {
    int32_t src[5] = {1, 2, 3, 4, 5};
    int32_t dest[5] = {0};
    
    /* Dest is NULL */
    if (safe_array_copy(NULL, 5, src, 5, 0, 5) != SAFE_ARRAY_ERROR_NULL_PTR) return false;
    
    /* Src is NULL */
    if (safe_array_copy(dest, 5, NULL, 5, 0, 5) != SAFE_ARRAY_ERROR_NULL_PTR) return false;
    
    return true;
}

/* Test Case 3: Out of Bounds Detection (Source Offset Overflow) */
static bool test_source_overflow(void) {
    int32_t src[5] = {1, 2, 3, 4, 5};
    int32_t dest[5] = {0};
    
    /* Offset (3) + Copy Length (3) = 6, which exceeds source size (5) */
    safe_array_status_t status = safe_array_copy(dest, 5, src, 5, 3, 3);
    
    return (status == SAFE_ARRAY_ERROR_OUT_OF_BOUNDS);
}

/* Test Case 4: Destination Capacity Limit Protection */
static bool test_destination_overflow(void) {
    int32_t src[5] = {1, 2, 3, 4, 5};
    int32_t dest[3] = {0}; /* Smaller destination */
    
    /* Attempting to copy 4 elements into a size 3 destination */
    safe_array_status_t status = safe_array_copy(dest, 3, src, 5, 0, 4);
    
    return (status == SAFE_ARRAY_ERROR_OUT_OF_BOUNDS);
}

/* Test Case 5: Memory Overlap Detection */
static bool test_memory_overlap(void) {
    int32_t arr[5] = {1, 2, 3, 4, 5};
    
    /* Pointing source and destination to overlapping segments of the same array memory block */
    safe_array_status_t status = safe_array_copy(&arr[2], 3, &arr[0], 5, 0, 3);
    
    return (status == SAFE_ARRAY_ERROR_OVERLAP);
}

int main(void) {
    printf("=======================================\n");
    printf("  STARTING EMBEDDED C LAB UNIT TESTS   \n");
    printf("=======================================\n");
    
    RUN_TEST(test_valid_copy);
    RUN_TEST(test_null_pointers);
    RUN_TEST(test_source_overflow);
    RUN_TEST(test_destination_overflow);
    RUN_TEST(test_memory_overlap);
    
    printf("=======================================\n");
    printf(" TEST RESULTS: %d/%d PASSED\n", tests_passed, tests_run);
    printf("=======================================\n");
    
    return (tests_passed == tests_run) ? 0 : 1;
}
