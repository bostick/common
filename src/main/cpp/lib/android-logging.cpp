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

#include "common/assert.h"
#include "common/unusual_message.h"

#include <android/log.h>

#include <cstdarg> // for va_list, va_start, va_arg, va_end
#include <cstring>
#include <cstdio>


#define TAG "android-logging"


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

void LogWarnAndCaptureUnusualV(const char *tag, const char *fmt, va_list args) {

    ASSERT(std::strlen(tag) <= 23); // Android logging tags can be at most 23 characters

    __android_log_vprint(ANDROID_LOG_WARN, tag, fmt, args);

    //
    // fine if truncated
    //
    char buf[1000];
    std::vsnprintf(buf, sizeof(buf), fmt, args);

    captureUnusualMessage(buf);
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
















