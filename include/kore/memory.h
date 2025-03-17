#ifndef _KORELIB_MEMORY_H
#define _KORELIB_MEMORY_H

#include <kore/types.h>

#ifdef KORE_CPP
extern "C" {
#endif

void kore_free(kore_ptr ptr);
kore_ptr kore_alloc(size_t size);
kore_ptr kore_realloc(kore_ptr ptr, size_t size);

size_t kore_leak();
size_t kore_size(kore_ptr ptr);

void kore_memory_register(const char* alias, u8 layout);
size_t kore_memory_unregister(u8 layout);

void kore_memory_free(kore_ptr ptr, u8 layout);
kore_ptr kore_memory_alloc(size_t size, u8 layout);
kore_ptr kore_memory_realloc(kore_ptr ptr, size_t size, u8 layout);

void kore_memory_print();
size_t kore_memory_leak();

void kore_memory_set_title(const char* title);
void kore_memory_set_color(KOREcolor fg, KOREcolor bg);

#ifdef KORE_CPP
}
#endif

#endif // _KORELIB_MEMORY_H