// Copyright (C) 2025 by Brenton Bostick
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

#if _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // disable warnings about localtime being unsafe on MSVC
#endif // _MSC_VER

#include "common/clock.h"

#undef NDEBUG

#include "common/abort.h"
#include "common/assert.h"
#include "common/error.h"
#include "common/platform.h"

#if IS_PLATFORM_ANDROID
#include <jni.h>
#endif // IS_PLATFORM_ANDROID

#if IS_PLATFORM_ANDROID || IS_PLATFORM_LINUX
#include <ctime> // for clock_gettime
#elif IS_PLATFORM_MACOS
#elif IS_PLATFORM_WINDOWS
#include <windows.h>
#include <sysinfoapi.h> // for GetTickCount64
#else
#error
#endif // IS_PLATFORM_ANDROID || IS_PLATFORM_LINUX

#include <chrono>
#include <cstring> // for strerror
#include <locale>


#define TAG "clock"


char nowStrBuf[FORMATTIME_LEN + 1];


#if IS_PLATFORM_ANDROID || IS_PLATFORM_LINUX

//
// don't use CLOCK_MONOTONIC_RAW on Android
// https://github.com/libsdl-org/SDL/commit/62d82ffc15b21fcc432fd9e0499c4585cd8d89c8
//

int64_t uptimeMillis(void) {

    timespec now; // NOLINT(*-pro-type-member-init)
    if (::clock_gettime(CLOCK_MONOTONIC, &now) == -1) {
        ABORT("clock_gettime: %s (%s)", std::strerror(errno), ErrorName(errno));
    }

    return (static_cast<int64_t>(now.tv_sec) * 1000) + (static_cast<int64_t>(now.tv_nsec) / 1000000);
}

int64_t uptimeMicros(void) {

    timespec now; // NOLINT(*-pro-type-member-init)
    if (::clock_gettime(CLOCK_MONOTONIC, &now) == -1) {
        ABORT("clock_gettime: %s (%s)", std::strerror(errno), ErrorName(errno));
    }

    return (static_cast<int64_t>(now.tv_sec) * 1000000) + (static_cast<int64_t>(now.tv_nsec) / 1000);
}

#elif IS_PLATFORM_MACOS

//
// see clock.mm
//

#elif IS_PLATFORM_WINDOWS

int64_t uptimeMillis(void) {

    return GetTickCount64();
}

#else
#error
#endif // IS_PLATFORM_ANDROID || IS_PLATFORM_LINUX


int64_t timeSinceEpochSeconds(void) {

    auto now = std::chrono::system_clock::now();

    auto epoch = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

    return epoch.count();
}

int64_t timeSinceEpochMillis(void) {

    auto now = std::chrono::system_clock::now();

    auto epoch = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    return epoch.count();
}


//
// compute the current time and store in nowStrBuf
//
void GrabNow(void) {

    time_t timer; // NOLINT(*-init-variables)
    if (std::time(&timer) == -1) {
        ABORT("time: %s (%s)", std::strerror(errno), ErrorName(errno));
    }

    formatTime(timer, nowStrBuf, sizeof(nowStrBuf));
}


void formatTime(time_t timeV, char *buf, size_t len) {

    tm *timeinfo; // NOLINT(*-init-variables)
    if (timeinfo = std::localtime(&timeV); timeinfo == nullptr) {
        ABORT("localtime: %s (%s)", std::strerror(errno), ErrorName(errno));
    }

    std::locale oldLocale;
    oldLocale = std::locale::global(std::locale::classic());

    //
    // "%F %X" is equivalent to "%Y-%m-%d %H:%M:%S"
    //
    if (std::strftime(buf, len, "%F %X", timeinfo) == 0) {
        ABORT("strftime returned 0");
    }

    std::locale::global(oldLocale);
}


//
// JNI functions
//

#if IS_PLATFORM_ANDROID

extern "C"
JNIEXPORT jlong JNICALL
Java_com_brentonbostick_common_Clock_timeSinceEpochMillisNative(JNIEnv *env, jclass clazz) {

    (void)env;
    (void)clazz;

    return timeSinceEpochMillis();
}

#endif // IS_PLATFORM_ANDROID
















