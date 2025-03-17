#ifndef _KORELIB_TYPES_H
#define _KORELIB_TYPES_H

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#if !defined(KORE_OS_WINDOWS) && !defined(KORE_OS_LINUX) && !defined(KORE_OS_UNKNOW) 
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
        #define KORE_OS_WINDOWS
    #elif defined(__linux__) || defined(__gnu_linux__)
        #define KORE_OS_LINUX 1
    #else
        #define KORE_OS_UNKNOW
    #endif
#endif

#ifdef __cplusplus
    #define KORE_CPP
#endif

#if defined(__GNUG__)
    #define KORE_COMPILER_GPP
#elif defined(__GNUC__)
    #define KORE_COMPILER_GCC
#elif defined(__clang__)
    #define KORE_COMPILER_CLANG
#endif

#if !defined(KORE_DEBUG) && !defined(KORE_RELEASE)
    #if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG) || !defined(_NDEBUG)
        #define KORE_DEBUG
    #endif

    #ifndef KORE_DEBUG
        #define KORE_RELEASE
    #endif
#endif

#define KORE_KB(count) (1024 * count)
#define KORE_MB(count) (1024 * 1024 * count)
#define KORE_GB(count) (1024 * 1024 * 1024 * count)

#define KORE_FILE_LINE __LINE__
#define KORE_FILE_NAME __FILE_NAME__

typedef signed char i8;
typedef signed short i16;
typedef signed long i32;
typedef signed long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef void* kore_ptr;

#define TRUE 1
#define FALSE 0

#ifndef __cplusplus

#define true 1
#define false 0

#endif // __cplusplus

typedef enum KOREtype {
    KORE_TYPE_NONE    = 0,
    KORE_TYPE_I8      = 1,
    KORE_TYPE_I16     = 2,
    KORE_TYPE_I32     = 4,
    KORE_TYPE_I64     = 8,
    KORE_TYPE_U8      = 16,
    KORE_TYPE_U16     = 32,
    KORE_TYPE_U32     = 64,
    KORE_TYPE_U64     = 128,
    KORE_TYPE_F32     = 256,
    KORE_TYPE_F64     = 512,
} KOREtype;

typedef enum KOREcolor {
    KORE_COLOR_BLACK     = 0x00,
    KORE_COLOR_RED       = 0x01,
    KORE_COLOR_GREEN     = 0x02,
    KORE_COLOR_YELLOW    = 0x03,
    KORE_COLOR_BLUE      = 0x04,
    KORE_COLOR_MAGENTA   = 0x05,
    KORE_COLOR_CYAN      = 0x06,
    KORE_COLOR_WHITE     = 0x07,
    KORE_COLOR_INTENSITY = 0x80
} KOREcolor;

typedef enum KORElog {
    KORE_LOG_FATAL  = 0,
    KORE_LOG_ERROR  = 1,
    KORE_LOG_WARN   = 2,
    KORE_LOG_INFO   = 3,
    KORE_LOG_DEBUG  = 4,
    KORE_LOG_TRACE  = 5
} KORElog;

#endif // _KORELIB_TYPES_H