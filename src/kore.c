#include <kore/kore.h>
#include <kore/types.h>
#include <kore/string.h>
#include <kore/memory.h>

#include <stdio.h>

u8 initialized = false;

extern u8 (*sys_init)();
extern u8 (*sys_terminate)();

static __attribute__((destructor(101))) void kore_destructor() {
    if (initialized) {
        fprintf(stderr, "\n[KORE INTERNAL]: Program terminated without terminating kore library.");
    }
    if (kore_memory_leak() > 0 || kore_leak() > 0) {
        fprintf(stderr, "\n[KORE INTERNAL]: Program terminated with memory leaks.\n");
        kore_memory_print();
    }
    fprintf(stderr, "\n");
};

u8 kore_init() {
    if (!sys_init()) {
        return false;
    }
    initialized = true;

    return true;
}
u8 kore_terminate() {
    if (kore_memory_leak() > 0 || kore_leak() > 0) {
        return false;
    }

    initialized = false;
    if (!sys_terminate()) {
        return false;
    }

    return true;
}

void kwrite_color(const char* buffer, size_t count, KOREcolor fg, KOREcolor bg) {
    kore_console_set_color(fg, bg);
    kwrite(buffer, count);
    kore_console_reset();
}
void kwrite_foreground(const char* buffer, size_t count, KOREcolor fg) {
    kore_console_set_foreground(fg);
    kwrite(buffer, count);
    kore_console_reset();
}
void kwrite_background(const char* buffer, size_t count, KOREcolor bg) {
    kore_console_set_background(bg);
    kwrite(buffer, count);
    kore_console_reset();
}

void kprint(const char* buffer) {
    kwrite(buffer, kstrlen(buffer));
}
void kprint_color(const char* buffer, KOREcolor fg, KOREcolor bg) {
    kore_console_set_color(fg, bg);
    kwrite(buffer, kstrlen(buffer));
    kore_console_reset();
}
void kprint_foreground(const char* buffer, KOREcolor fg) {
    kore_console_set_foreground(fg);
    kwrite(buffer, kstrlen(buffer));
    kore_console_reset();
}
void kprint_background(const char* buffer, KOREcolor bg) {
    kore_console_set_background(bg);
    kwrite(buffer, kstrlen(buffer));
    kore_console_reset();
}

void kvprintf(const char* format, va_list args) {
    const char* msg = kstrvdupf(format, args);
    kwrite(msg, kstrlen(msg));
    kore_free(msg);
}
void kvprintf_color(KOREcolor fg, KOREcolor bg, const char* format, va_list args) {
    const char* msg = kstrvdupf(format, args);
    kore_console_set_color(fg, bg);
    kwrite(msg, kstrlen(msg));
    kore_console_reset();
    kore_free(msg);
}
void kvprintf_foreground(KOREcolor fg, const char* format, va_list args) {
    const char* msg = kstrvdupf(format, args);
    kore_console_set_foreground(fg);
    kwrite(msg, kstrlen(msg));
    kore_console_reset();
    kore_free(msg);
}
void kvprintf_background(KOREcolor bg, const char* format, va_list args) {
    const char* msg = kstrvdupf(format, args);
    kore_console_set_background(bg);
    kwrite(msg, kstrlen(msg));
    kore_console_reset();
    kore_free(msg);
}

void kprintf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    kvprintf(format, args);
    va_end(args);
}
void kprintf_color(KOREcolor fg, KOREcolor bg, const char* format, ...) {
    va_list args;
    va_start(args, format);
    kvprintf_color(fg, bg, format, args);
    va_end(args);
}
void kprintf_foreground(KOREcolor fg, const char* format, ...) {
    va_list args;
    va_start(args, format);
    kvprintf_foreground(fg, format, args);
    va_end(args);
}
void kprintf_background(KOREcolor bg, const char* format, ...) {
    va_list args;
    va_start(args, format);
    kvprintf_background(bg, format, args);
    va_end(args);
}

void kerror_color(const char* buffer, KOREcolor fg, KOREcolor bg) {
    kore_console_set_color(fg, bg);
    kerror(buffer);
    kore_console_reset();
}
void kerror_foreground(const char* buffer, KOREcolor fg) {
    kore_console_set_foreground(fg);
    kerror(buffer);
    kore_console_reset();
}
void kerror_background(const char* buffer, KOREcolor bg) {
    kore_console_set_background(bg);
    kerror(buffer);
    kore_console_reset();
}

void kverrorf(const char* format, va_list args) {
    const char* msg = kstrvdupf(format, args);
    kerror(msg);
    kore_free(msg);
}
void kverrorf_color(KOREcolor fg, KOREcolor bg, const char* format, va_list args) {
    const char* msg = kstrvdupf(format, args);
    kore_console_set_color(fg, bg);
    kerror(msg);
    kore_console_reset();
    kore_free(msg);
}
void kverrorf_foreground(KOREcolor fg, const char* format, va_list args) {
    const char* msg = kstrvdupf(format, args);
    kore_console_set_foreground(fg);
    kerror(msg);
    kore_console_reset();
    kore_free(msg);
}
void kverrorf_background(KOREcolor bg, const char* format, va_list args) {
    const char* msg = kstrvdupf(format, args);
    kore_console_set_background(bg);
    kerror(msg);
    kore_console_reset();
    kore_free(msg);
}

void kerrorf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    kverrorf(format, args);
    va_end(args);
}
void kerrorf_color(KOREcolor fg, KOREcolor bg, const char* format, ...) {
    va_list args;
    va_start(args, format);
    kverrorf_color(fg, bg, format, args);
    va_end(args);
}
void kerrorf_foreground(KOREcolor fg, const char* format, ...) {
    va_list args;
    va_start(args, format);
    kverrorf_foreground(fg, format, args);
    va_end(args);
}
void kerrorf_background(KOREcolor bg, const char* format, ...) {
    va_list args;
    va_start(args, format);
    kverrorf_background(bg, format, args);
    va_end(args);
}