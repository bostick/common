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

//
// keep compilable with C and C++
//

#pragma once

#include <stdint.h> // for int64_t NOLINT(*-deprecated-headers)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//
// monotonic
//
int64_t uptimeMillis(void);

//
// NOT monotonic
//
int64_t timeSinceEpochSeconds(void);

//
// This may TECHNICALLY be the same clock as System.currentTime() on Java, but just use
// timeSinceEpochMillis() everywhere to be consistent, even on Java.
//
// NOT monotonic
//
int64_t timeSinceEpochMillis(void);

extern char nowStrBuf[80];

void GrabNow(void);

#ifdef __cplusplus
}
#endif // __cplusplus
















