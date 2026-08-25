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

#include "common/abort.h"

#include <string>


#define TAG "logging"


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

static void LogWarnAndCaptureUnusual(const char *tag, const char *fmt, ...) {
    va_list args; // NOLINT(*-init-variables)
    va_start(args, fmt);
    LogWarnAndCaptureUnusualV(tag, fmt, args);
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
// default log level is TRACE
LOG_decl LOGF_expanded = LogFatal;
LOG_decl LOGE_expanded = LogError;
LOG_decl LOGE_andCaptureUnusual_expanded = LogErrorAndCaptureUnusual;
LOG_decl LOGW_expanded = LogWarn;
LOG_decl LOGW_andCaptureUnusual_expanded = LogWarnAndCaptureUnusual;
LOG_decl LOGI_expanded = LogInfo;
LOG_decl LOGD_expanded = LogDebug;
LOG_decl LOGT_expanded = LogTrace;

LOG_declV LOGF_expandedV = LogFatalV;
LOG_declV LOGE_expandedV = LogErrorV;
LOG_declV LOGW_expandedV = LogWarnV;
LOG_declV LOGI_expandedV = LogInfoV;
LOG_declV LOGD_expandedV = LogDebugV;
LOG_declV LOGT_expandedV = LogTraceV;


LogTracer::LogTracer(const char *tag, const char *function) :
    tag(tag),
    function(function) {
    //
    // passing in tag, so cannot use LOGT macro
    //
    LOGT_expanded(tag, "enter %s" COMMON_LOGGING_C, function);
}

LogTracer::~LogTracer() {
    LOGT_expanded(tag, "exit %s" COMMON_LOGGING_C, function);
}

DebugLogTracer::DebugLogTracer(const char *tag, const char *function, const char *file, int line) :
        tag(tag),
        function(function),
        file(file),
        line(line) {
    //
    // passing in tag, so cannot use LOGT macro
    //
    LOGT_expanded(tag, "enter %s %s:%d" COMMON_LOGGING_C, function, file, line);
}

DebugLogTracer::~DebugLogTracer() {
    LOGT_expanded(tag, "exit %s %s:%d" COMMON_LOGGING_C, function, file, line);
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
    LOGE("%s", (buf + (i * 500)));
    LOGE();
}
















