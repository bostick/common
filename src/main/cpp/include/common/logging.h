// Copyright (C) 2024 by Brenton Bostick
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

#include <stdarg.h> // for va_list NOLINT(*-deprecated-headers)


//
// greater = more noise
//
#define LOGLEVEL_ERROR 0
#define LOGLEVEL_UNUSUAL 0
#define LOGLEVEL_WARN 1
#define LOGLEVEL_INFO 2
#define LOGLEVEL_DEBUG 3
#define LOGLEVEL_TRACE 4

// var arg
typedef void (*LOG_decl)(const char *tag, const char *fmt, ...);

// va_list
typedef void (*LOG_declV)(const char *tag, const char *fmt, va_list args);


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// var arg

#if __GNUC__ || __clang__

//
// declare that LOGE_expanded et al take printf-style arguments
//
// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-format-function-attribute
//

extern __attribute__ ((format (printf, 2, 3))) LOG_decl LOGF_expanded;
extern __attribute__ ((format (printf, 2, 3))) LOG_decl LOGE_expanded;
extern __attribute__ ((format (printf, 2, 3))) LOG_decl LOGU_expanded;
extern __attribute__ ((format (printf, 2, 3))) LOG_decl LOGW_expanded;
extern __attribute__ ((format (printf, 2, 3))) LOG_decl LOGI_expanded;
extern __attribute__ ((format (printf, 2, 3))) LOG_decl LOGD_expanded;
extern __attribute__ ((format (printf, 2, 3))) LOG_decl LOGT_expanded;

#else // __GNUC__ || __clang__

extern LOG_decl LOGF_expanded;
extern LOG_decl LOGE_expanded;
extern LOG_decl LOGU_expanded;
extern LOG_decl LOGW_expanded;
extern LOG_decl LOGI_expanded;
extern LOG_decl LOGD_expanded;
extern LOG_decl LOGT_expanded;

#endif // __GNUC__ || __clang__


// va_list

//
// the va_list functions LOGE_expandedV et al can be called by code that already has a va_list
//

extern LOG_declV LOGF_expandedV;
extern LOG_declV LOGE_expandedV;
extern LOG_declV LOGU_expandedV;
extern LOG_declV LOGW_expandedV;
extern LOG_declV LOGI_expandedV;
extern LOG_declV LOGD_expandedV;
extern LOG_declV LOGT_expandedV;

#ifdef __cplusplus
}
#endif // __cplusplus


#if IS_PLATFORM_ANDROID

//
// doing:
// LOGI()
//
// is completely fine.
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

#define LOGE(fmt, ...) LOGE_expanded(TAG, fmt "" __VA_OPT__(,) __VA_ARGS__)
#define LOGU(fmt, ...) LOGU_expanded(TAG, fmt "" __VA_OPT__(,) __VA_ARGS__)
#define LOGW(fmt, ...) LOGW_expanded(TAG, fmt "" __VA_OPT__(,) __VA_ARGS__)
#define LOGI(fmt, ...) LOGI_expanded(TAG, fmt "" __VA_OPT__(,) __VA_ARGS__)
#define LOGD(fmt, ...) LOGD_expanded(TAG, fmt "" __VA_OPT__(,) __VA_ARGS__)
#define LOGT(fmt, ...) LOGT_expanded(TAG, fmt "" __VA_OPT__(,) __VA_ARGS__)

#else // IS_PLATFORM_ANDROID

//
// the "\n" in the below definitions serves 2 purposes:
// 1. allowing LOGI() to be expanded properly (the same purpose as "" above)
// 2. adding the trailing "\n" that is needed on non-Android platforms
//

#define LOGE(fmt, ...) LOGE_expanded(TAG, fmt "\n" __VA_OPT__(,) __VA_ARGS__)
#define LOGU(fmt, ...) LOGU_expanded(TAG, fmt "\n" __VA_OPT__(,) __VA_ARGS__)
#define LOGW(fmt, ...) LOGW_expanded(TAG, fmt "\n" __VA_OPT__(,) __VA_ARGS__)
#define LOGI(fmt, ...) LOGI_expanded(TAG, fmt "\n" __VA_OPT__(,) __VA_ARGS__)
#define LOGD(fmt, ...) LOGD_expanded(TAG, fmt "\n" __VA_OPT__(,) __VA_ARGS__)
#define LOGT(fmt, ...) LOGT_expanded(TAG, fmt "\n" __VA_OPT__(,) __VA_ARGS__)

#endif // IS_PLATFORM_ANDROID


#ifdef __cplusplus

class LogTracer {
    const char *tag;
    const char *function;
    const char *file;
    int line;
public:
    LogTracer(const char *tag, const char *function, const char *file, int line);

    ~LogTracer();
};

#define LOG_ENTRY_EXIT_FOR(tag, x, y, z) \
    LogTracer SomeLongNameThatIsNotLikelyToBeUsedInTheFunctionLogger(tag, x, y, z)

#define LOG_ENTRY_EXIT \
  LOG_ENTRY_EXIT_FOR(TAG, __FUNCTION__, __FILE__, __LINE__)

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















