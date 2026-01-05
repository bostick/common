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

#pragma once


//
// Provide preprocessor defines for platform identification.
//
// platform.h USED to have these definitions:
// #define PLATFORM_ANDROID 1
// #define PLATFORM_IOS 2
// #define PLATFORM_MACOS 3
// #define PLATFORM_WINDOWS 4
// #define PLATFORM_LINUX 5
//
// but other libraries may simply check for these definitions and get confused.
//
// For example, raylib thinks that it was building on Android even when not on Android, because of this logic:
//
// https://github.com/raysan5/raylib/blob/fecf56e15aaba160aefe14b241de19262a20ab3e/src/rcore.c#L333
//
// ```
// #elif defined(PLATFORM_ANDROID)
//    #include "rcore_android.c"
// #else
// ```
//
// So keep things simple and only define IS_PLATFORM_ANDROID etc. and PLATFORM_STRING
//
// These make less sense to only test for being defined and can be considered an error if used like this:
//
// #if defined(IS_PLATFORM_ANDROID)
// #endif
//


//
// there is an outside chance these macros are already defined
//
#if defined(IS_PLATFORM_ANDROID) || defined(IS_PLATFORM_IOS) || defined(IS_PLATFORM_MACOS) || defined(IS_PLATFORM_WINDOWS) || defined(IS_PLATFORM_LINUX) || defined(PLATFORM_STRING)
#error Platform macros already defined (IS_PLATFORM_ANDROID, IS_PLATFORM_IOS, IS_PLATFORM_MACOS, IS_PLATFORM_WINDOWS, IS_PLATFORM_LINUX, PLATFORM_STRING)
#endif // defined(IS_PLATFORM_ANDROID) || defined(IS_PLATFORM_IOS) || defined(IS_PLATFORM_MACOS) || defined(IS_PLATFORM_WINDOWS) || defined(IS_PLATFORM_LINUX) || defined(PLATFORM_STRING)


#if defined(__ANDROID__)

//
// https://android.googlesource.com/platform/bionic/+/HEAD/docs/defines.md
//

#define IS_PLATFORM_ANDROID 1
#define PLATFORM_STRING "android"

#elif __APPLE__

#include "TargetConditionals.h"

#if TARGET_OS_IOS

#define IS_PLATFORM_IOS 1
#define PLATFORM_STRING "ios"

#elif TARGET_OS_OSX

#define IS_PLATFORM_MACOS 1
#define PLATFORM_STRING "macos"

#else // TARGET_OS_IOS
#error Unknown Apple platform
#endif // TARGET_OS_IOS

#elif defined(_WIN32)

#define IS_PLATFORM_WINDOWS 1
#define PLATFORM_STRING "windows"

#elif defined(__linux__)

#define IS_PLATFORM_LINUX 1
#define PLATFORM_STRING "linux"

#else
#error Unknown platform
#endif // defined(__ANDROID__)
















