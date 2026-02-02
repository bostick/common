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

#include "common/abort.h"

#include "common/logging.h"
#include "common/unusual_message.h"

#include <cstdlib> // for abort


#define TAG "abort"


void ABORT_expanded(const char *tag, const char *fmt, ...) {

    va_list args; // NOLINT(*-init-variables)
    va_start(args, fmt);
    ABORT_expandedV(tag, fmt, args);

    //
    // unreachable
    //
    // va_end(args);
}


void ABORT_expandedV(const char *tag, const char *fmt, va_list args) {

    LOGF_expandedV(tag, fmt, args);

    //
    // fine if truncated
    //
    char buf[1000];
    std::vsnprintf(buf, sizeof(buf), fmt, args);

    captureUnusualMessageWhileAborting(buf);

    std::abort();
}
















