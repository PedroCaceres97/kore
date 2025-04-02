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

u8 kmemcmp(const void* src, const void* dst, size_t count);
void kmemcpy(void* dst, const void* src, size_t count);
void kmemset(void* dst, unsigned char value, size_t count);
void kmemzro(void* dst, size_t count);

u8 kstrcmp(const char* src, const char* dst);
u8 kstrncmp(const char* src, const char* dst, size_t count);

void kstrcpy(char* dst, const char* src);
void kstrncpy(char* dst, const char* src, size_t count);

size_t kstrlen(const char* src);
size_t kstrnlen(const char* src, size_t count);

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