#include <kore/string.h>
#include <kore/memory.h>

#include <stdio.h>
#include <string.h>

void kzero(const char* src, size_t count) {
    kmemset(src, 0, count);
}

char* kstrdup(const char* src) {
    size_t size = kstrlen(src);
    char* dst = kore_alloc(size + 1);
    kmemcpy(dst, src, size);
    return dst;
}
char* kstrndup(const char* src, size_t count) {
    char* dst = kore_alloc(count + 1);
    kmemcpy(dst, src, count);
    return dst;
}
char* kstrdupf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    char* buffer = kstrvdupf(format, args);
    va_end(args);
    return buffer;
}
char* kstrvdupf(const char* format, va_list args) {
    va_list copy;
    va_copy(copy, args);

    size_t count = vsnprintf(NULL, 0, format, copy) + 1;
    char* buffer = kore_alloc(count + 1);
    vsnprintf(buffer, count + 1, format, args);

    va_end(copy);
    return buffer;
}

void kstrtail(char* dst, const char* tail) {
    size_t size = kstrlen(tail);
    kmemcpy(&dst[kstrlen(dst) - size - 1], tail, size + 1);
}
void kstrctail(char* dst, const char* tail, char chr) {
    const char* pos = strrchr(dst, chr) + 1;
    size_t index = kstrlen(dst) - kstrlen(pos);
    kmemcpy(&dst[index], tail, kstrlen(tail) + 1);
}