#pragma once

#include <stdio.h>
#include "types.h"

typedef struct
{
    bool has_error;
    const char* error;

    size_t bytes_len;
    u8* bytes;
} FSReadResult;

typedef struct
{
    bool has_error;
    const char* error;

    size_t bytes_written;
} FSWriteResult;

FSReadResult fs_read(const char* path);

void fr_free(FSReadResult* result);