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

#include "common/logging.h"

#undef NDEBUG

#include "common/abort.h"
#include "common/assert.h"
#include "common/platform.h"
#include "common/unusual_message.h"

#if IS_PLATFORM_ANDROID
#include <android/log.h>
#endif // IS_PLATFORM_ANDROID

#include <cstdio> // for fprintf, stderr
#include <cstdarg> // for va_list, va_start, va_arg, va_end


#define TAG "logging"


static void LogFatalV(const char *tag, const char *fmt, va_list args);
static void LogErrorV(const char *tag, const char *fmt, va_list args);
static void LogErrorAndCaptureUnusualV(const char *tag, const char *fmt, va_list args);
static void LogWarnV(const char *tag, const char *fmt, va_list args);
static void LogInfoV(const char *tag, const char *fmt, va_list args);
static void LogDebugV(const char *tag, const char *fmt, va_list args);
static void LogTraceV(const char *tag, const char *fmt, va_list args);
static void LogNullV(const char *tag, const char *fmt, va_list args);


static void LogFatal(const char *tag, const char *fmt, ...) {
    va_list args; // NOLINT(*-init-variables)
    va_start(args, fmt);
    LogFatalV(tag, fmt, args);
    va_end(args);
}

static void LogError(const char *tag, const char *fmt, ...) {
    va_list args; // NOLINT(*-init-variables)
    va_start(args, fmt);
    LogErrorV(tag, fmt, args);
    va_end(args);
}

static void LogErrorAndCaptureUnusual(const char *tag, const char *fmt, ...) {
    va_list args; // NOLINT(*-init-variables)
    va_start(args, fmt);
    LogErrorAndCaptureUnusualV(tag, fmt, args);
    va_end(args);
}

static void LogWarn(const char *tag, const char *fmt, ...) {
    va_list args; // NOLINT(*-init-variables)
    va_start(args, fmt);
    LogWarnV(tag, fmt, args);
    va_end(args);
}

static void LogInfo(const char *tag, const char *fmt, ...) {
    va_list args; // NOLINT(*-init-variables)
    va_start(args, fmt);
    LogInfoV(tag, fmt, args);
    va_end(args);
}

static void LogDebug(const char *tag, const char *fmt, ...) {
    va_list args; // NOLINT(*-init-variables)
    va_start(args, fmt);
    LogDebugV(tag, fmt, args);
    va_end(args);
}

static void LogTrace(const char *tag, const char *fmt, ...) {
    va_list args; // NOLINT(*-init-variables)
    va_start(args, fmt);
    LogTraceV(tag, fmt, args);
    va_end(args);
}

static void LogNull(const char *tag, const char *fmt, ...) {
    (void)tag;
    (void)fmt;
}


//
// define the various LogXXXV
//

#if IS_PLATFORM_ANDROID

void LogFatalV(const char *tag, const char *fmt, va_list args) {

    ASSERT(std::strlen(tag) <= 23); // Android logging tags can be at most 23 characters

    __android_log_vprint(ANDROID_LOG_FATAL, tag, fmt, args);
}

void LogErrorV(const char *tag, const char *fmt, va_list args) {

    ASSERT(std::strlen(tag) <= 23); // Android logging tags can be at most 23 characters

    __android_log_vprint(ANDROID_LOG_ERROR, tag, fmt, args);
}

void LogErrorAndCaptureUnusualV(const char *tag, const char *fmt, va_list args) {

    ASSERT(std::strlen(tag) <= 23); // Android logging tags can be at most 23 characters

    __android_log_vprint(ANDROID_LOG_ERROR, tag, fmt, args);

    //
    // fine if truncated
    //
    char buf[1000];
    std::vsnprintf(buf, sizeof(buf), fmt, args);

    captureUnusualMessage(buf);
}

void LogWarnV(const char *tag, const char *fmt, va_list args) {

    ASSERT(std::strlen(tag) <= 23); // Android logging tags can be at most 23 characters

    __android_log_vprint(ANDROID_LOG_WARN, tag, fmt, args);
}

void LogInfoV(const char *tag, const char *fmt, va_list args) {

    ASSERT(std::strlen(tag) <= 23); // Android logging tags can be at most 23 characters

    __android_log_vprint(ANDROID_LOG_INFO, tag, fmt, args);
}

void LogDebugV(const char *tag, const char *fmt, va_list args) {

    ASSERT(std::strlen(tag) <= 23); // Android logging tags can be at most 23 characters

    __android_log_vprint(ANDROID_LOG_DEBUG, tag, fmt, args);
}

void LogTraceV(const char *tag, const char *fmt, va_list args) {

    ASSERT(std::strlen(tag) <= 23); // Android logging tags can be at most 23 characters

    __android_log_vprint(ANDROID_LOG_VERBOSE, tag, fmt, args);
}

void LogNullV(const char *tag, const char *fmt, va_list args) {

    ASSERT(std::strlen(tag) <= 23); // Android logging tags can be at most 23 characters

    (void)fmt;
    (void)args;
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


void LogErrorAndCaptureUnusualV(const char *tag, const char *fmt, va_list args) {

    (void)tag;

    std::vfprintf(stderr, fmt, args);

    //
    // fine if truncated
    //
    char buf[1000];
    std::vsnprintf(buf, sizeof(buf), fmt, args);

    captureUnusualMessage(buf);
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

void LogNullV(const char *tag, const char *fmt, va_list args) { // NOLINT(readability-non-const-parameter)
    (void)tag;
    (void)fmt;
    (void)args;
}

#endif // IS_PLATFORM_ANDROID


//
// default log level is TRACE
LOG_decl LOGF_expanded = LogFatal;
LOG_decl LOGE_expanded = LogError;
LOG_decl LOGE_andCaptureUnusual_expanded = LogErrorAndCaptureUnusual;
LOG_decl LOGW_expanded = LogWarn;
LOG_decl LOGI_expanded = LogInfo;
LOG_decl LOGD_expanded = LogDebug;
LOG_decl LOGT_expanded = LogTrace;

LOG_declV LOGF_expandedV = LogFatalV;
LOG_declV LOGE_expandedV = LogErrorV;
LOG_declV LOGW_expandedV = LogWarnV;
LOG_declV LOGI_expandedV = LogInfoV;
LOG_declV LOGD_expandedV = LogDebugV;
LOG_declV LOGT_expandedV = LogTraceV;


LogTracer::LogTracer(const char *tag, const char *function, const char *file, int line) :
    tag(tag),
    function(function),
    file(file),
    line(line) {
    //
    // passing in tag, so cannot use LOGT macro
    //
#if IS_PLATFORM_ANDROID
    LOGT_expanded(tag, "enter %s %s:%d", function, file, line);
#else
    LOGT_expanded(tag, "enter %s %s:%d\n", function, file, line);
#endif // IS_PLATFORM_ANDROID
}

LogTracer::~LogTracer() {
#if IS_PLATFORM_ANDROID
    LOGT_expanded(tag, "exit %s %s:%d", function, file, line);
#else
    LOGT_expanded(tag, "exit %s %s:%d\n", function, file, line);
#endif // IS_PLATFORM_ANDROID
}


void SetLogLevel(int level) {

    //
    // LOGF_expanded and LOGE_expanded never change, so no need to set
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
        default:
        ABORT("invalid log level: %d", level);
    }
}


void LOGE_chunks(const char *buf, size_t len) {

    size_t chunkCount = (len / 500);

    size_t i; // NOLINT(*-init-variables)
    for (i = 0; i < chunkCount; i++) {
        LOGE("%s", std::string(buf + (i * 500), 500).c_str());
    }
    LOGE("%s", buf + (i * 500));
    LOGE();
}
















