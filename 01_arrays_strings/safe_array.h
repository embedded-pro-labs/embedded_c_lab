#ifndef SAFE_ARRAY_H
#define SAFE_ARRAY_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {
    SAFE_ARRAY_SUCCESS = 0,
    SAFE_ARRAY_ERROR_NULL_PTR,
    SAFE_ARRAY_ERROR_OUT_OF_BOUNDS,
    SAFE_ARRAY_ERROR_OVERLAP,
    SAFE_ARRAY_ERROR_INVALID_SIZE
} safe_array_status_t;

safe_array_status_t safe_array_copy(
    int32_t *dest,
    size_t dest_sz,
    const int32_t *src,
    size_t src_sz,
    size_t src_offset,
    size_t copy_len
);

#endif /* SAFE_ARRAY_H */
