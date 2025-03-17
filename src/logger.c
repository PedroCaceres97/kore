#include <kore/kore.h>
#include <kore/logger.h>
#include <kore/string.h>
#include <kore/memory.h>

typedef struct KORElevel {
    KOREcolor color;
    const char* alias;
} KORElevel;

static KORElevel levels[6] = {
    {KORE_COLOR_MAGENTA | KORE_COLOR_INTENSITY, "[FATAL]: "},
    {KORE_COLOR_RED     | KORE_COLOR_INTENSITY, "[ERROR]: "},
    {KORE_COLOR_YELLOW  | KORE_COLOR_INTENSITY, " [WARN]: "},
    {KORE_COLOR_CYAN    | KORE_COLOR_INTENSITY, " [INFO]: "},
    {KORE_COLOR_BLUE    | KORE_COLOR_INTENSITY, "[DEBUG]: "},
    {KORE_COLOR_WHITE   | KORE_COLOR_INTENSITY, "[TRACE]: "},
};

void klog(const char* format, ...) {
    va_list args;
    va_start(args, format);
    kvprintf("\n[KORE]: %s\n", args);
    va_end(args);
}

void kore_logger_log(KORElog level, const char* format, ...) {
    char* message = 0;
    kstrvf(format, message);
    kprint_foreground(levels[level].alias, levels[level].color);
    kprintf("%s\n", message);
    kore_free(message);
}

void kore_logger_set_color(KORElog level, KOREcolor color) {
    levels[level].color = color;
}
void kore_logger_set_alias(KORElog level, const char* alias) {
    levels[level].alias = alias;
}