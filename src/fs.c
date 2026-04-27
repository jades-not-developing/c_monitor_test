#include "fs.h"

#include <stdlib.h>
#include <string.h>

#define FR_RETURN_ERR() {\
    result.error = strerror(errno);\
    result.has_error = 1;\
    return result;\
}

void fr_free(FSReadResult* result)
{
    result->has_error = true;
    result->error = "Result has been freed";

    if (result->bytes) free(result->bytes);
    result->bytes_len = 0;
}

FSReadResult fs_read(const char* path)
{
    FSReadResult result = {0};
    result.error = "Unknown error";

    FILE* f = fopen(path, "r");
    if (f == NULL) FR_RETURN_ERR();

    if (fseek(f, 0L, SEEK_END) == -1) FR_RETURN_ERR();
    result.bytes_len = ftell(f);
    if (result.bytes_len == -1) FR_RETURN_ERR();
    if (fseek(f, 0, SEEK_SET) == -1) FR_RETURN_ERR();

    result.bytes = malloc(result.bytes_len * sizeof(u8));

    fread(result.bytes, result.bytes_len, 1, f);
    if (result.bytes == NULL) FR_RETURN_ERR();
    if (ferror(f)) FR_RETURN_ERR();
    if (fclose(f) != 0) FR_RETURN_ERR();

    result.bytes[result.bytes_len] = '\0';

    return result;
}
