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

#include "common/clock.h"
#include "common/platform.h"

#if IS_PLATFORM_ANDROID || IS_PLATFORM_LINUX
#include <ctime> // for clock_gettime
#elif IS_PLATFORM_MACOS

#elif IS_PLATFORM_WINDOWS

#else
#error
#endif // IS_PLATFORM_ANDROID || IS_PLATFORM_LINUX

#include <chrono>


#if IS_PLATFORM_ANDROID || IS_PLATFORM_LINUX

int64_t uptimeMillis(void) {

    timespec now; // NOLINT(*-pro-type-member-init)

    clock_gettime(CLOCK_MONOTONIC, &now);

    return static_cast<int64_t>(now.tv_sec) * 1000 + static_cast<int64_t>(now.tv_nsec) / 1000000;
}

#elif IS_PLATFORM_MACOS

// CURRENTLY UNIMPLEMENTED

#elif IS_PLATFORM_WINDOWS

// CURRENTLY UNIMPLEMENTED

#else
#error
#endif // IS_PLATFORM_ANDROID || IS_PLATFORM_LINUX


int64_t wallClockSeconds(void) {

    auto now = std::chrono::system_clock::now();

    auto epoch = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

    return epoch.count();
}
















