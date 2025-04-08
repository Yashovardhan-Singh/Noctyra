#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// Unsigned Integer Types
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

// Signed Integer Types
typedef signed char      i8;
typedef signed short     i16;
typedef signed int       i32;
typedef signed long long i64;

// Floating Point Types
typedef float  f32;
typedef double f64;

typedef void* ptr;
typedef char* str;

typedef u8 bool;

#define true  1
#define false 0

#if defined(__x86_64__) || defined(__aarch64__) || defined(_M_x64)
    typedef u64 usize;
#else
    typedef u32 usize;
#endif

// Platform-Specific Type Definitions
#if defined(_WIN32) || defined(_WIN64)
    typedef unsigned long ulong;
    typedef signed long slong;
#elif defined(__linux__) || defined(__APPLE__) || defined(__unix__)
    typedef unsigned long ulong;
    typedef signed long slong;
#endif

// Generic logging macro
#define LOG(level, msg, ...) fprintf(stdout, "[%s] %s:%d: " msg "\n", level, __FILE__, __LINE__, ##__VA_ARGS__)

// Specific case defines
#define E_LOG(msg, ...) LOG("ERROR", msg, ##__VA_ARGS__)    // error
#define W_LOG(msg, ...) LOG("WARN", msg, ##__VA_ARGS__)     // warn
#define I_LOG(msg, ...) LOG("INFO", msg, ##__VA_ARGS__)     // info

static inline f32 PixelToNdcX(f32 x, f32 screenWidth) {
    return (x / screenWidth) * 2.0f - 1.0f;
}

static inline f32 PixelToNdcY(f32 y, f32 screenHeight) {
    return (y / screenHeight) * 2.0f - 1.0f;
}


#endif // UTILS_H
