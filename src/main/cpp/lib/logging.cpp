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

#include "common/logging.h"

#include "common/assert.h"
#include "common/clock.h"
#include "common/platform.h"

#if IS_PLATFORM_ANDROID
#include <android/log.h>
#endif // IS_PLATFORM_ANDROID

#include <string>
#include <chrono>
#include <cstdio> // for fprintf, stderr
#include <ctime> // for localtime, strftime
#include <cstdarg> // for va_list, va_start, va_arg, va_end
#include <cstring> // for strchr


#define TAG "logging"


void LogFatalV(const char *tag, const char *fmt, va_list args);
void LogErrorV(const char *tag, const char *fmt, va_list args);
void LogWarnV(const char *tag, const char *fmt, va_list args);
void LogInfoV(const char *tag, const char *fmt, va_list args);
void LogDebugV(const char *tag, const char *fmt, va_list args);
void LogTraceV(const char *tag, const char *fmt, va_list args);


void LogFatal(const char *tag, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogFatalV(tag, fmt, args);
    va_end(args);
}

void LogError(const char *tag, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogErrorV(tag, fmt, args);
    va_end(args);
}

void LogWarn(const char *tag, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogWarnV(tag, fmt, args);
    va_end(args);
}

void LogInfo(const char *tag, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogInfoV(tag, fmt, args);
    va_end(args);
}

void LogDebug(const char *tag, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogDebugV(tag, fmt, args);
    va_end(args);
}

void LogTrace(const char *tag, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogTraceV(tag, fmt, args);
    va_end(args);
}

void LogNull(const char *tag, const char *fmt, ...) {
    (void)tag;
    (void)fmt;
}


#if IS_PLATFORM_ANDROID

void LogFatalV(const char *tag, const char *fmt, va_list args) {
    __android_log_vprint(ANDROID_LOG_FATAL, tag, fmt, args);
}

void LogErrorV(const char *tag, const char *fmt, va_list args) {
    __android_log_vprint(ANDROID_LOG_ERROR, tag, fmt, args);
}

void LogWarnV(const char *tag, const char *fmt, va_list args) {
    __android_log_vprint(ANDROID_LOG_WARN, tag, fmt, args);
}

void LogInfoV(const char *tag, const char *fmt, va_list args) {
    __android_log_vprint(ANDROID_LOG_INFO, tag, fmt, args);
}

void LogDebugV(const char *tag, const char *fmt, va_list args) {
    __android_log_vprint(ANDROID_LOG_DEBUG, tag, fmt, args);
}

void LogTraceV(const char *tag, const char *fmt, va_list args) {
    __android_log_vprint(ANDROID_LOG_VERBOSE, tag, fmt, args);
}

#else

void LogFatalV(const char *tag, const char *fmt, va_list args) {
    (void)tag;
    std::vfprintf(stderr, fmt, args);
    std::fflush(stderr);
}

void LogErrorV(const char *tag, const char *fmt, va_list args) {
    (void)tag;
    std::vfprintf(stderr, fmt, args);
    std::fflush(stderr);
}

void LogWarnV(const char *tag, const char *fmt, va_list args) {
    (void)tag;
    std::vfprintf(stderr, fmt, args);
    std::fflush(stderr);
}

void LogInfoV(const char *tag, const char *fmt, va_list args) {
    (void)tag;
    std::vfprintf(stderr, fmt, args);
    std::fflush(stderr);
}

void LogDebugV(const char *tag, const char *fmt, va_list args) {
    (void)tag;
    std::vfprintf(stderr, fmt, args);
    std::fflush(stderr);
}

void LogTraceV(const char *tag, const char *fmt, va_list args) {
    (void)tag;
    std::vfprintf(stderr, fmt, args);
    std::fflush(stderr);
}

#endif // IS_PLATFORM_ANDROID

void LogNullV(const char *tag, const char *fmt, va_list args) {
    (void)tag;
    (void)fmt;
    (void)args;
}


//
// default log level is INFO
//
LOG_decl LOGF_expanded = LogFatal;
LOG_decl LOGE_expanded = LogError;
LOG_decl LOGW_expanded = LogWarn;
LOG_decl LOGI_expanded = LogInfo;
LOG_decl LOGD_expanded = LogNull;
LOG_decl LOGT_expanded = LogNull;

LOG_declV LOGF_expandedV = LogFatalV;
LOG_declV LOGE_expandedV = LogErrorV;
LOG_declV LOGW_expandedV = LogWarnV;
LOG_declV LOGI_expandedV = LogInfoV;
LOG_declV LOGD_expandedV = LogNullV;
LOG_declV LOGT_expandedV = LogNullV;


LogTracer::LogTracer(const char *tag, const char *function, const char *file, int line) :
    tag(tag),
    function(function),
    file(file),
    line(line) {
    GrabNow();
    LOGT_expanded(tag, "%s: enter %s %s:%d\n", nowStrBuf, function, file, line);
}

LogTracer::~LogTracer() {
    GrabNow();
    LOGT_expanded(tag, "%s: exit %s %s:%d\n", nowStrBuf, function, file, line);
}


void SetLogLevel(int level) {

    //
    // LOGE_expanded and LOGU_expanded never change, so no need to set
    //

    switch (level) {
    case LOGLEVEL_FATAL:
    case LOGLEVEL_ERROR: {
        LOGW_expanded = LogNull;
        LOGI_expanded = LogNull;
        LOGD_expanded = LogNull;
        LOGT_expanded = LogNull;

        LOGW_expandedV = LogNullV;
        LOGI_expandedV = LogNullV;
        LOGD_expandedV = LogNullV;
        LOGT_expandedV = LogNullV;
        break;
    }
    case LOGLEVEL_WARN: {
        LOGW_expanded = LogWarn;
        LOGI_expanded = LogNull;
        LOGD_expanded = LogNull;
        LOGT_expanded = LogNull;

        LOGW_expandedV = LogWarnV;
        LOGI_expandedV = LogNullV;
        LOGD_expandedV = LogNullV;
        LOGT_expandedV = LogNullV;
        break;
    }
    case LOGLEVEL_INFO: {
        LOGW_expanded = LogWarn;
        LOGI_expanded = LogInfo;
        LOGD_expanded = LogNull;
        LOGT_expanded = LogNull;

        LOGW_expandedV = LogWarnV;
        LOGI_expandedV = LogInfoV;
        LOGD_expandedV = LogNullV;
        LOGT_expandedV = LogNullV;
        break;
    }
    case LOGLEVEL_DEBUG: {
        LOGW_expanded = LogWarn;
        LOGI_expanded = LogInfo;
        LOGD_expanded = LogDebug;
        LOGT_expanded = LogNull;

        LOGW_expandedV = LogWarnV;
        LOGI_expandedV = LogInfoV;
        LOGD_expandedV = LogDebugV;
        LOGT_expandedV = LogNullV;
        break;
    }
    case LOGLEVEL_TRACE: {
        LOGW_expanded = LogWarn;
        LOGI_expanded = LogInfo;
        LOGD_expanded = LogDebug;
        LOGT_expanded = LogTrace;

        LOGW_expandedV = LogWarnV;
        LOGI_expandedV = LogInfoV;
        LOGD_expandedV = LogDebugV;
        LOGT_expandedV = LogTraceV;
        break;
    }
    default: {
        ABORT("invalid log level: %d", level);
    }
    }
}



















