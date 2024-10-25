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

#include "common/abort.h"
#include "common/platform.h"

#ifdef NDEBUG

#if IS_PLATFORM_WINDOWS

//
// based on example here:
//
// https://learn.microsoft.com/en-us/cpp/preprocessor/pragma-directives-and-the-pragma-keyword?view=msvc-170
//

#define ASSERT(cond) \
    do { \
        _Pragma("warning(suppress: 4127)") /* C4127 conditional expression is constant */ \
        ((void)0); \
    } while (0)

#else

#define ASSERT(cond) \
    do { \
        ((void)0); \
    } while (0)

#endif // IS_PLATFORM_WINDOWS

#else // NDEBUG

#if IS_PLATFORM_WINDOWS

//
// if cond is false, then abort
//
#define ASSERT(cond) \
    do { \
        _Pragma("warning(suppress: 4127)") /* C4127 conditional expression is constant */ \
        if (!(cond)) { \
            ABORT("ASSERTION FAILED: %s %s:%d", #cond, __FILE__, __LINE__); \
        } \
    } while (0)

#else

//
// if cond is false, then abort
//
#define ASSERT(cond) \
    do { \
        if (!(cond)) { \
            ABORT("ASSERTION FAILED: %s %s:%d", #cond, __FILE__, __LINE__); \
        } \
    } while (0)

#endif // IS_PLATFORM_WINDOWS

#endif // NDEBUG
















