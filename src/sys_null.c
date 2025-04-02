#include <kore/kore.h>
#include "kore_sys.h"

void    (*kread)(char* buffer, size_t count)                    = null_kread;
void    (*kignore)()                                            = null_kignore;
void    (*kwrite)(const char* buffer, size_t count)             = null_kwrite;
void    (*kerror)(const char* buffer)                           = null_kerror;

u8  (*kore_is_dir)(const char* path)                        = null_kore_is_dir;
u8  (*kore_is_file)(const char* path, const char* file)     = null_kore_is_file;
u8  (*kore_make_dir)(const char* path)                      = null_kore_make_dir;
u8  (*kore_make_path)(const char* path)                     = null_kore_make_path;

void    (*kore_console_clear)()                                 = null_kore_console_clear;
void    (*kore_console_reset)()                                 = null_kore_console_reset;
void    (*kore_console_set_color)(KOREcolor fg, KOREcolor bg)   = null_kore_console_set_color;
void    (*kore_console_set_foreground)(KOREcolor fg)            = null_kore_console_set_foreground;
void    (*kore_console_set_background)(KOREcolor bg)            = null_kore_console_set_background;

static void report(const char* function) {
    fprintf(stderr, "(null system report)\n[KORE]: Calling %s wihtout initializing first\n", function);
}

void null_kread(char* buffer, size_t count) {
    report("kread");
}
void null_kignore() {
    report("kignore");
}
void null_kwrite(const char* buffer, size_t count) {
    report("kwrite");
}
void null_kerror(const char* buffer) {
    report("kerror");
}

u8 null_kore_is_dir(const char* path) {
    report("kore_is_dir");
    return false;
}
u8 null_kore_is_file(const char* path, const char* file) {
    report("kore_is_file");
    return false;
}
u8 null_kore_make_dir(const char* path) {
    report("kore_make_dir");
    return false;
}
u8 null_kore_make_path(const char* path) {
    report("kore_make_path");
    return false;
}

void null_kore_console_clear() {
    report("kore_console_clear");
}
void null_kore_console_reset() {
    report("kore_console_reset");
}
void null_kore_console_set_color(KOREcolor fg, KOREcolor bg) {
    report("kore_console_set_color");
}
void null_kore_console_set_foreground(KOREcolor fg) {
    report("kore_console_set_foreground");
}
void null_kore_console_set_background(KOREcolor bg) {
    report("kore_console_set_background");
}