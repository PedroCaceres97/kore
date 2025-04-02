#ifndef _KORELIB_H
#define _KORELIB_H

#include <kore/types.h>

#ifdef KORE_CPP
extern "C" {
#endif

u8 kore_init();
u8 kore_terminate();

extern void (*kread)(char* buffer, size_t count);
extern void (*kignore)();

extern void (*kwrite)(const char* buffer, size_t count);
void kwrite_color(const char* buffer, size_t count, KOREcolor fg, KOREcolor bg);
void kwrite_foreground(const char* buffer, size_t count, KOREcolor fg);
void kwrite_background(const char* buffer, size_t count, KOREcolor bg);

extern void (*kerror)(const char* buffer);
void kerror_color(const char* buffer, KOREcolor fg, KOREcolor bg);
void kerror_foreground(const char* buffer, KOREcolor fg);
void kerror_background(const char* buffer, KOREcolor bg);

void kprint(const char* buffer);
void kprint_color(const char* buffer, KOREcolor fg, KOREcolor bg);
void kprint_foreground(const char* buffer, KOREcolor fg);
void kprint_background(const char* buffer, KOREcolor bg);

void kvprintf(const char* format, va_list args);
void kvprintf_color(KOREcolor fg, KOREcolor bg, const char* format, va_list args);
void kvprintf_foreground(KOREcolor fg, const char* format, va_list args);
void kvprintf_background(KOREcolor bg, const char* format, va_list args);

void kprintf(const char* format, ...);
void kprintf_color(KOREcolor fg, KOREcolor bg, const char* format, ...);
void kprintf_foreground(KOREcolor fg, const char* format, ...);
void kprintf_background(KOREcolor bg, const char* format, ...);

void kverrorf(const char* format, va_list args);
void kverrorf_color(KOREcolor fg, KOREcolor bg, const char* format, va_list args);
void kverrorf_foreground(KOREcolor fg, const char* format, va_list args);
void kverrorf_background(KOREcolor bg, const char* format, va_list args);

void kerrorf(const char* format, ...);
void kerrorf_color(KOREcolor fg, KOREcolor bg, const char* format, ...);
void kerrorf_foreground(KOREcolor fg, const char* format, ...);
void kerrorf_background(KOREcolor bg, const char* format, ...);

extern u8 (*kore_is_dir)(const char* path);
extern u8 (*kore_is_file)(const char* path, const char* file);
extern u8 (*kore_make_dir)(const char* path);
extern u8 (*kore_make_path)(const char* path);

extern void (*kore_console_clear)();
extern void (*kore_console_reset)();
extern void (*kore_console_set_color)(KOREcolor fg, KOREcolor bg);
extern void (*kore_console_set_foreground)(KOREcolor fg);
extern void (*kore_console_set_background)(KOREcolor bg);

#ifdef KORE_CPP
}
#endif

#endif // _KORELIB_H