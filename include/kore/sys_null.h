#ifndef _KORELIB_SYSTEM_NULL_H
#define _KORELIB_SYSTEM_NULL_H

#include <kore/types.h>

#ifdef KORE_CPP
extern "C" {
#endif

void null_kignore();
void null_kwrite(const char* buffer, size_t count);
void null_kerror(const char* buffer);

u8 null_kore_is_dir(const char* path);
u8 null_kore_is_file(const char* path, const char* file);
u8 null_kore_make_dir(const char* path);
u8 null_kore_make_path(const char* path);

void null_kore_console_clear();
void null_kore_console_reset();
void null_kore_console_set_color(KOREcolor fg, KOREcolor bg);
void null_kore_console_set_foreground(KOREcolor fg);
void null_kore_console_set_background(KOREcolor bg);

#ifdef KORE_CPP
}
#endif

#endif // _KORELIB_SYSTEM_NULL_H