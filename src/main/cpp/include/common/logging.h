// Copyright (C) 2026 by Brenton Bostick
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial
// portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//
// keep compilable with C and C++
//

#pragma once

#include "common/platform.h"

#ifdef __cplusplus
#include <cstdarg> // for va_list
#include <cstddef> // for size_t
#else
#include <stdarg.h> // for va_list
#include <stddef.h> // for size_t
#endif // __cplusplus


//
// there is an outside chance these macros are already defined
//
#if defined(LOGLEVEL_FATAL) || defined(LOGLEVEL_ERROR) || defined(LOGLEVEL_WARN) || defined(LOGLEVEL_INFO) || defined(LOGLEVEL_DEBUG) || defined(LOGLEVEL_TRACE)
#error Log level macros already defined (LOGLEVEL_FATAL, LOGLEVEL_ERROR, LOGLEVEL_WARN, LOGLEVEL_INFO, \
    LOGLEVEL_DEBUG, LOGLEVEL_TRACE), most likely from another logging framework. Remove previous logging framework.
#endif // defined(LOGLEVEL_FATAL) || defined(LOGLEVEL_ERROR) || defined(LOGLEVEL_WARN) || defined(LOGLEVEL_INFO) || defined(LOGLEVEL_DEBUG) || defined(LOGLEVEL_TRACE)


//
// arguments for SetLogLevel
//
// greater = more noise
//
#define LOGLEVEL_FATAL (-1)
#define LOGLEVEL_ERROR 0
#define LOGLEVEL_WARN 1
#define LOGLEVEL_INFO 2
#define LOGLEVEL_DEBUG 3
#define LOGLEVEL_TRACE 4


// var arg
typedef void (*LOG_decl)(const char *tag, const char *fmt, ...); // NOLINT(*-use-using)

// va_list
typedef void (*LOG_declV)(const char *tag, const char *fmt, va_list args); // NOLINT(*-use-using)


#if __GNUC__ || __clang__

//
// declare that LOGE_expanded et al take printf-style arguments
//
// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-format-function-attribute
//

#define PRINTF_ATTRIBUTE __attribute__ ((format (printf, 2, 3)))

#else

#define PRINTF_ATTRIBUTE

#endif // __GNUC__ || __clang__


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// var arg

extern PRINTF_ATTRIBUTE LOG_decl LOGF_expanded;
extern PRINTF_ATTRIBUTE LOG_decl LOGE_expanded;
extern PRINTF_ATTRIBUTE LOG_decl LOGE_andCaptureUnusual_expanded;
extern PRINTF_ATTRIBUTE LOG_decl LOGW_expanded;
extern PRINTF_ATTRIBUTE LOG_decl LOGW_andCaptureUnusual_expanded;
extern PRINTF_ATTRIBUTE LOG_decl LOGI_expanded;
extern PRINTF_ATTRIBUTE LOG_decl LOGD_expanded;
extern PRINTF_ATTRIBUTE LOG_decl LOGT_expanded;

// va_list

//
// the va_list functions LOGE_expandedV et al can be called by code that already has a va_list
//

//
// the caller of LOGF_expandedV should abort immediately after calling LOGF_expandedV
//
extern LOG_declV LOGF_expandedV;
extern LOG_declV LOGE_expandedV;
extern LOG_declV LOGW_expandedV;
extern LOG_declV LOGI_expandedV;
extern LOG_declV LOGD_expandedV;
extern LOG_declV LOGT_expandedV;

#ifdef __cplusplus
}
#endif // __cplusplus


#undef PRINTF_ATTRIBUTE


#if IS_PLATFORM_ANDROID

//
// LOGI() expands into LOGI_expanded(TAG, "")
//
// the old definition of:
// LOGI_expanded(TAG, fmt "" __VA_OPT__(,) __VA_ARGS__)
//
// meant that LOGI() expanded into LOGI_expanded(TAG, )
//
// and there is no easy way to get rid of the trailing comma.
//
// References such as:
// https://gcc.gnu.org/onlinedocs/cpp/Macro-Arguments.html
//
// explain "You can leave macro arguments empty"
//
// LOGI("%s", "foo") expands into LOGI_expanded(TAG, "%s" "" , "foo") -> LOGI_expanded(TAG, "%s", "foo")
//

#define COMMON_LOGGING_C ""

#else

//
// the "\n" in the below definition serves 2 purposes:
// 1. allowing LOGI() to be expanded properly (the same purpose as "" above)
// 2. adding the trailing "\n" that is needed on non-Android platforms
//

#define COMMON_LOGGING_C "\n"

#endif // IS_PLATFORM_ANDROID


//
// must use -Wno-gnu-zero-variadic-macro-arguments if getting warnings like:
// warning: must specify at least one argument for '...' parameter of variadic macro
//
// seems to be an issue with clang:
// https://stackoverflow.com/questions/78605260/error-must-specify-at-least-one-argument-for-parameter-of-variadic-macro
// https://github.com/llvm/llvm-project/issues/76375
//

//
// various defines DISABLE_LOGF, DISABLE_LOGE, etc. may be set to 1 disable LOGF, LOGE, etc. at compile time.
//
// all of this crazy macro business is to treat the arguments as used
//
// inspired by: https://stackoverflow.com/a/11763277
//

#define GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME

#define LOG0() \
    do {} while (false)

#define LOG1(a) \
    do { (void)a; } while (false)

#define LOG2(a, b) \
    do { (void)a; (void)b; } while (false)

#define LOG3(a, b, c) \
    do { (void)a; (void)b; (void)c; } while (false)

#define LOG4(a, b, c, d) \
    do { (void)a; (void)b; (void)c; (void)d; } while (false)

#define LOG5(a, b, c, d, e) \
    do { (void)a; (void)b; (void)c; (void)d; (void)e; } while (false)

#define LOG6(a, b, c, d, e, f) \
    do { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; } while (false)

#define LOG7(a, b, c, d, e, f, g) \
    do { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; } while (false)

#define LOG8(a, b, c, d, e, f, g, h) \
    do { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; } while (false)


//
// define LOGF
//
#if DISABLE_LOGF
#define LOGF(fmt, ...) \
    GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, LOG8, LOG7, LOG6, LOG5, LOG4, LOG3, LOG2, LOG1, LOG0)(__VA_ARGS__)
#else
#define LOGF(fmt, ...) \
    LOGF_expanded(TAG, fmt COMMON_LOGGING_C __VA_OPT__(,) __VA_ARGS__)
#endif // DISABLE_LOGF


//
// define LOGE
//
#if DISABLE_LOGE
#define LOGE(...) \
    GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, LOG8, LOG7, LOG6, LOG5, LOG4, LOG3, LOG2, LOG1, LOG0)(__VA_ARGS__)
#else
#define LOGE(fmt, ...) \
    LOGE_expanded(TAG, fmt COMMON_LOGGING_C __VA_OPT__(,) __VA_ARGS__)
#endif // DISABLE_LOGE


//
// define LOGE_andCaptureUnusual
//
#if DISABLE_LOGE
#define LOGE_andCaptureUnusual(fmt, ...) \
    GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, LOG8, LOG7, LOG6, LOG5, LOG4, LOG3, LOG2, LOG1, LOG0)(__VA_ARGS__)
#else
#define LOGE_andCaptureUnusual(fmt, ...) \
    LOGE_andCaptureUnusual_expanded(TAG, fmt COMMON_LOGGING_C __VA_OPT__(,) __VA_ARGS__)
#endif // DISABLE_LOGE


//
// define LOGW
//
#if DISABLE_LOGW
#define LOGW(fmt, ...) \
    GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, LOG8, LOG7, LOG6, LOG5, LOG4, LOG3, LOG2, LOG1, LOG0)(__VA_ARGS__)
#else
#define LOGW(fmt, ...) \
    LOGW_expanded(TAG, fmt COMMON_LOGGING_C __VA_OPT__(,) __VA_ARGS__)
#endif // DISABLE_LOGW


//
// define LOGW_andCaptureUnusual
//
#if DISABLE_LOGW
#define LOGW_andCaptureUnusual(fmt, ...) \
    GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, LOG8, LOG7, LOG6, LOG5, LOG4, LOG3, LOG2, LOG1, LOG0)(__VA_ARGS__)
#else
#define LOGW_andCaptureUnusual(fmt, ...) \
    LOGW_andCaptureUnusual_expanded(TAG, fmt COMMON_LOGGING_C __VA_OPT__(,) __VA_ARGS__)
#endif // DISABLE_LOGW


//
// define LOGI
//
#if DISABLE_LOGI
#define LOGI(fmt, ...) \
    GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, LOG8, LOG7, LOG6, LOG5, LOG4, LOG3, LOG2, LOG1, LOG0)(__VA_ARGS__)
#else
#define LOGI(fmt, ...) \
    LOGI_expanded(TAG, fmt COMMON_LOGGING_C __VA_OPT__(,) __VA_ARGS__)
#endif // DISABLE_LOGI


//
// define LOGD
//
#if DISABLE_LOGD
#define LOGD(fmt, ...) \
    GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, LOG8, LOG7, LOG6, LOG5, LOG4, LOG3, LOG2, LOG1, LOG0)(__VA_ARGS__)
#else
#define LOGD(fmt, ...) \
    LOGD_expanded(TAG, fmt COMMON_LOGGING_C __VA_OPT__(,) __VA_ARGS__)
#endif // DISABLE_LOGD


//
// define LOGT
//
#if DISABLE_LOGT
#define LOGT(fmt, ...) \
    GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, LOG8, LOG7, LOG6, LOG5, LOG4, LOG3, LOG2, LOG1, LOG0)(__VA_ARGS__)
#else
#define LOGT(fmt, ...) \
    LOGT_expanded(TAG, fmt COMMON_LOGGING_C __VA_OPT__(,) __VA_ARGS__)
#endif // DISABLE_LOGT


void LOGE_chunks(const char *buf, size_t len);


#ifdef __cplusplus

class LogTracer {
private:

    const char *tag;
    const char *function;

public:

    LogTracer(const char *tag, const char *function);
    ~LogTracer();
};

class DebugLogTracer {
private:

    const char *tag;
    const char *function;
    const char *file;
    int line;

public:

    DebugLogTracer(const char *tag, const char *function, const char *file, int line);
    ~DebugLogTracer();
};

//
// if LOCAL_DEBUGGING, then include __FILE__ and __LINE__
//
#if LOCAL_DEBUGGING

#define COMMON_LOGGING_LOG_ENTRY_EXIT_FOR(tag, x, y, z) \
    DebugLogTracer SomeLongNameThatIsNotLikelyToBeUsedInTheFunctionLogger(tag, x, y, z)

#else

#define COMMON_LOGGING_LOG_ENTRY_EXIT_FOR(tag, x, y, z) \
    LogTracer SomeLongNameThatIsNotLikelyToBeUsedInTheFunctionLogger(tag, x)

#endif // LOCAL_DEBUGGING

//
// Place LOG_ENTRY_EXIT at start of function definition and log entry and exit.
//
// LOG_ENTRY_EXIT uses RAII and is C++-only
//
#define LOG_ENTRY_EXIT \
    COMMON_LOGGING_LOG_ENTRY_EXIT_FOR(TAG, __FUNCTION__, __FILE__, __LINE__)

#else

#define LOG_ENTRY_EXIT

#endif // __cplusplus


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void SetLogLevel(int level);

#ifdef __cplusplus
}
#endif // __cplusplus
















