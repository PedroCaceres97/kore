#include <kore/string.h>
#include <kore/memory.h>

#include <stdio.h>
#include <string.h>

extern u8 asm_kmemcmp(const void* src, const void* dst, size_t count);
extern void asm_kmemcpy(void* dst, const void* src, size_t count);
extern void asm_kmemset(void* dst, unsigned char value, size_t count);
extern void asm_kmemzro(void* dst, size_t count);

extern u8 asm_kstrcmp(const char* src, const char* dst);
extern u8 asm_kstrncmp(const char* src, const char* dst, size_t count);

extern void asm_kstrcpy(char* dst, const char* src);
extern void asm_kstrncpy(char* dst, const char* src, size_t count);

extern size_t asm_kstrlen(const char* src);
extern size_t asm_kstrnlen(const char* src, size_t count);

u8 kmemcmp(const void* src, const void* dst, size_t count) {
#ifdef KORE_USE_STD
    return memcmp(src, dst, count) == 0;
#else
    return asm_kmemcmp(src, dst, count);
#endif
}
void kmemcpy(void* dst, const void* src, size_t count) {
#ifdef KORE_USE_STD
    memcpy(dst, src, count);
#else
    asm_kmemcpy(dst, src, count);
#endif
}
void kmemset(void* dst, unsigned char value, size_t count) {
#ifdef KORE_USE_STD
    memset(dst, value, count);
#else
    asm_kmemset(dst, value, count);
#endif
}
void kmemzro(void* dst, size_t count) {
#ifdef KORE_USE_STD
    memset(dst, 0, count);
#else
    kmemzro(dst, count);
#endif
}

u8 kstrcmp(const char* src, const char* dst) {
#ifdef KORE_USE_STD
    return strcmp(src, dst) == 0;
#else
    return asm_kstrcmp(src, dst);
#endif
}
u8 kstrncmp(const char* src, const char* dst, size_t count) {
#ifdef KORE_USE_STD
    return strncmp(src, dst, count) == 0;
#else
    return asm_kstrncmp(src, dst, count);
#endif
}

void kstrcpy(char* dst, const char* src) {
#ifdef KORE_USE_STD
    strcpy(dst, src);
#else
    asm_kstrcpy(dst, src);
#endif
}
void kstrncpy(char* dst, const char* src, size_t count) {
#ifdef KORE_USE_STD
    strncpy(dst, src, count);
#else
    asm_kstrncpy(dst, src, count);
#endif
}

size_t kstrlen(const char* src) {
#ifdef KORE_USE_STD
    return strlen(src);
#else
    return asm_kstrlen(src);
#endif
}
size_t kstrnlen(const char* src, size_t count) {
#ifdef KORE_USE_STD
    return strnlen(src, count);
#else
    return asm_kstrnlen(src, count);
#endif
}

char* kstrvdupf(const char* format, va_list args) {
    va_list copy;
    va_copy(copy, args);

    size_t count = vsnprintf(NULL, 0, format, copy) + 1;
    char* buffer = kore_alloc(count);
    vsnprintf(buffer, count, format, args);

    va_end(copy);
    return buffer;
}
char* kstrdupf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    char* buffer = kstrvdupf(format, args);
    va_end(args);
    return buffer;
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

void kstrtail(char* dst, const char* tail) {
    size_t size = kstrlen(tail);
    kmemcpy(&dst[kstrlen(dst) - size - 1], tail, size + 1);
}
void kstrctail(char* dst, const char* tail, char chr) {
    const char* pos = strrchr(dst, chr) + 1;
    size_t index = kstrlen(dst) - kstrlen(pos);
    kmemcpy(&dst[index], tail, kstrlen(tail) + 1);
}