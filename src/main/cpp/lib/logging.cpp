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

#include "common/platform.h"

#if IS_PLATFORM_ANDROID
#include <android/log.h>
#endif // IS_PLATFORM_ANDROID

#include <string>
#include <chrono>
#include <cstdio> // for fprintf, stderr
#include <ctime>
#include <cstdarg> // for va_list, va_start, va_arg, va_end
#include <cstring> // for strchr


#define TAG "logging"


void GrabNow();


time_t timer;
struct tm* timeinfo;
char nowStrBuf[80];


#if IS_PLATFORM_ANDROID

void LogVarArgError(const char *tag, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  __android_log_print(ANDROID_LOG_ERROR, tag, fmt, args);
  va_end(args);
}

void LogVarArgUnusual(const char *tag, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  __android_log_print(ANDROID_LOG_ERROR, tag, fmt, args);
  va_end(args);
}

void LogVarArgWarn(const char *tag, const char *fmt, ...)  {
  va_list args;
  va_start(args, fmt);
  __android_log_print(ANDROID_LOG_WARN, tag, fmt, args);
  va_end(args);
}

void LogVarArgInfo(const char *tag, const char *fmt, ...)  {
  va_list args;
  va_start(args, fmt);
  __android_log_print(ANDROID_LOG_INFO, tag, fmt, args);
  va_end(args);
}

void LogVarArgDebug(const char *tag, const char *fmt, ...)  {
  va_list args;
  va_start(args, fmt);
  __android_log_print(ANDROID_LOG_DEBUG, tag, fmt, args);
  va_end(args);
}

void LogVarArgTrace(const char *tag, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  __android_log_print(ANDROID_LOG_VERBOSE, tag, fmt, args);
  va_end(args);
}

#else // IS_PLATFORM_ANDROID

void LogVarArgError(const char *tag, const char *fmt, ...) {

  (void)tag;

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fflush(stderr);
}

void LogVarArgUnusual(const char *tag, const char *fmt, ...) {

  (void)tag;

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fflush(stderr);
}

void LogVarArgWarn(const char *tag, const char *fmt, ...) {

  (void)tag;

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fflush(stderr);
}

void LogVarArgInfo(const char *tag, const char *fmt, ...) {

  (void)tag;

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fflush(stderr);
}

void LogVarArgDebug(const char *tag, const char *fmt, ...) {

  (void)tag;

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fflush(stderr);
}

void LogVarArgTrace(const char *tag, const char *fmt, ...) {

  (void)tag;

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fflush(stderr);
}

#endif // IS_PLATFORM_ANDROID

void LogVarArgNull(const char *tag, const char *fmt, ...) {
  (void)tag;
  (void)fmt;
}


//
// default log level is INFO
//
LOG_decl LOGE_expanded = LogVarArgError;
LOG_decl LOGU_expanded = LogVarArgUnusual;
LOG_decl LOGW_expanded = LogVarArgWarn;
LOG_decl LOGI_expanded = LogVarArgInfo;
LOG_decl LOGD_expanded = LogVarArgDebug;
LOG_decl LOGT_expanded = LogVarArgNull;



LogTracer::LogTracer(const char *tag, const char* function, const char* file, int line) :
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


//
// compute the current time and store in nowStrBuf
//
void GrabNow() {
  time(&timer);
  timeinfo = localtime(&timer);
  //
  // "%F %X" is equivalent to "%Y-%m-%d %H:%M:%S"
  //
  strftime(nowStrBuf, 80, "%F %X", timeinfo);
}


void SetLogLevel(int level) {

  switch (level) {
  case LOGLEVEL_ERROR: {
    LOGE_expanded = LogVarArgError;
    LOGU_expanded = LogVarArgUnusual;
    LOGW_expanded = LogVarArgNull;
    LOGI_expanded = LogVarArgNull;
    LOGD_expanded = LogVarArgNull;
    LOGT_expanded = LogVarArgNull;
    break;
  }
  case LOGLEVEL_WARN: {
    LOGE_expanded = LogVarArgError;
    LOGU_expanded = LogVarArgUnusual;
    LOGW_expanded = LogVarArgWarn;
    LOGI_expanded = LogVarArgNull;
    LOGD_expanded = LogVarArgNull;
    LOGT_expanded = LogVarArgNull;
    break;
  }
  case LOGLEVEL_INFO: {
    LOGE_expanded = LogVarArgError;
    LOGU_expanded = LogVarArgUnusual;
    LOGW_expanded = LogVarArgWarn;
    LOGI_expanded = LogVarArgInfo;
    LOGD_expanded = LogVarArgNull;
    LOGT_expanded = LogVarArgNull;
    break;
  }
  case LOGLEVEL_DEBUG: {
    LOGE_expanded = LogVarArgError;
    LOGU_expanded = LogVarArgUnusual;
    LOGW_expanded = LogVarArgWarn;
    LOGI_expanded = LogVarArgInfo;
    LOGD_expanded = LogVarArgDebug;
    LOGT_expanded = LogVarArgNull;
    break;
  }
  case LOGLEVEL_TRACE: {
    LOGE_expanded = LogVarArgError;
    LOGU_expanded = LogVarArgUnusual;
    LOGW_expanded = LogVarArgWarn;
    LOGI_expanded = LogVarArgInfo;
    LOGD_expanded = LogVarArgDebug;
    LOGT_expanded = LogVarArgTrace;
    break;
  }
  default: {
    ASSERT(false);
  }
  }
}



















