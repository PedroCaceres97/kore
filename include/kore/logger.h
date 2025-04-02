#ifndef _KORELIB_LOGGER_H
#define _KORELIB_LOGGER_H

#include <kore/types.h>

#define kore_fatal(format, ...) kore_logger_log(KORE_LOG_FATAL, format, ##__VA_ARGS__)
#define kore_error(format, ...) kore_logger_log(KORE_LOG_ERROR, format, ##__VA_ARGS__)
#define kore_warn(format, ...)  kore_logger_log(KORE_LOG_WARN,  format, ##__VA_ARGS__)
#define kore_info(format, ...)  kore_logger_log(KORE_LOG_INFO,  format, ##__VA_ARGS__)

#ifdef KORE_DEBUG
    #define kore_debug(format, ...) kore_logger_log(KORE_LOG_DEBUG, format, ##__VA_ARGS__)
    #define kore_trace(format, ...) kore_logger_log(KORE_LOG_TRACE, format, ##__VA_ARGS__)
#else
    #define kore_debug(format, ...)
    #define kore_trace(format, ...)
#endif

#ifdef KORE_CPP
extern "C" {
#endif

void klog(const char* format, ...); 

void kore_logger_log(KORElog level, const char* format, ...);

void kore_logger_set_color(KORElog level, KOREcolor color);
void kore_logger_set_alias(KORElog level, const char* alias);

#ifdef KORE_CPP
}
#endif

#endif // _KORELIB_LOGGER_H