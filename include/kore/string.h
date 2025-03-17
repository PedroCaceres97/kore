#ifndef _KORELIB_STRING_H
#define _KORELIB_STRING_H

#include <kore/types.h>

#define kstrvf(format, buffer)              \
    va_list args;                           \
    va_start(args, format);                 \
    buffer = kstrvdupf(format, args);       \
    va_end(args);                           \

#ifdef KORE_CPP
extern "C" {
#endif

extern u8 kmemcmp(const void* src, const void* dst, size_t count);
extern void kmemcpy(const void* src, const void* dst, size_t count);
extern void kmemset(const void* src, unsigned char value, size_t count);

extern u8 kstrcmp(const char* src, const char* dst);
extern u8 kstrncmp(const char* src, const char* dst, size_t count);

extern void kstrcpy(const char* src, const char* dst);
extern void kstrncpy(const char* src, const char* dst, size_t count);

extern size_t kstrlen(const char* src);
extern size_t kstrnlen(const char* src, size_t count);

void kzero(const char* src, size_t count);

char* kstrdup(const char* src);
char* kstrndup(const char* src, size_t count);
char* kstrdupf(const char* format, ...);
char* kstrvdupf(const char* format, va_list args);

void kstrtail(char* dst, const char* tail);
void kstrctail(char* dst, const char* tail, char chr);

#ifdef KORE_CPP
}
#endif

#endif // _KORELIB_STRING_H