/**
 * @file safe_array.c
 * @brief Implementation of boundary-safe array copy.
 * @note Designed for high-reliability embedded systems (MISRA-C aligned).
 * @author Embedded Pro Labs
 */

#include "safe_array.h"

safe_array_status_t safe_array_copy(
    int32_t *dest,
    size_t dest_sz,
    const int32_t *src,
    size_t src_sz,
    size_t src_offset,
    size_t copy_len
) {
    /* 1. Defensive NULL pointer validation */
    if (dest == NULL || src == NULL) {
        return SAFE_ARRAY_ERROR_NULL_PTR;
    }

    /* 2. Validate array sizes are non-zero to prevent division by zero or invalid operations */
    if (dest_sz == 0 || src_sz == 0 || copy_len == 0) {
        return SAFE_ARRAY_ERROR_INVALID_SIZE;
    }

    /* 3. Prevent Integer Overflow: Check if offset + copy_len exceeds source size */
    if (src_offset > src_sz || copy_len > (src_sz - src_offset)) {
        return SAFE_ARRAY_ERROR_OUT_OF_BOUNDS;
    }

    /* 4. Validate destination bounds */
    if (copy_len > dest_sz) {
        return SAFE_ARRAY_ERROR_OUT_OF_BOUNDS;
    }

    /* 5. Memory Overlap Protection: Check if arrays overlap in RAM to prevent corruption */
    if ((src < dest && (src + src_sz) > dest) || 
        (dest < src && (dest + dest_sz) > src)) {
        return SAFE_ARRAY_ERROR_OVERLAP;
    }

    /* 6. Perform the copy safely once all boundaries are verified */
    for (size_t i = 0; i < copy_len; i++) {
        dest[i] = src[src_offset + i];
    }

    return SAFE_ARRAY_SUCCESS;
}
