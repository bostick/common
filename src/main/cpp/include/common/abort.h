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


#if __GNUC__ || __clang__

//
// declare that ABORT_expanded takes printf-style arguments
//
// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-format-function-attribute
//

#define PRINTF_ATTRIBUTE __attribute__ ((format (printf, 2, 3)))

#else

#define PRINTF_ATTRIBUTE

#endif // __GNUC__ || __clang__

#ifdef __cplusplus

//
// [[noreturn]] since C++11
//

#define NORETURN_ATTRIBUTE [[noreturn]]

#else

//
// [[noreturn]] since C23 and C23 is not yet generally available
//

#define NORETURN_ATTRIBUTE /*[[noreturn]]*/

#endif // __cplusplus


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// var arg

PRINTF_ATTRIBUTE void ABORT_expanded NORETURN_ATTRIBUTE (const char *tag, const char *fmt, ...);

// va_list

//
// the va_list function ABORT_expandedV can be called by code that already has a va_list
//

void ABORT_expandedV NORETURN_ATTRIBUTE (const char *tag, const char *fmt, va_list args);

#ifdef __cplusplus
}
#endif // __cplusplus


#undef PRINTF_ATTRIBUTE
#undef NORETURN_ATTRIBUTE
















