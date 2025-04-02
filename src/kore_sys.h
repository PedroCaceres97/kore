#ifndef KORELIB_KORE_SYS_H
#define KORELIB_KORE_SYS_H

#include <kore/types.h>
#include <stdio.h>

#ifdef KORE_SYS_USE_STD

#include <string.h>
#define __sys_strlen__(string) strlen(string)
#define __sys_strdup__(string) strdup(string)
#define __sys_strcmp__(src, dst) strcmp(src, dst) == 0

#else

#include <kore/string.h>
#define __sys_strlen__(string) kstrlen(string)
#define __sys_strdup__(string) kstrdup(string)
#define __sys_strcmp__(src, dst) kstrcmp(src, dst)

#endif // KORE_SYS_USE_STD

#ifdef KORE_CPP
extern "C" {
#endif

void null_kread(char* buffer, size_t count);
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

#endif // KORELIB_KORE_SYS_H