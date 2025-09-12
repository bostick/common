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

#pragma once

#include "common/status.h"

#include <string>
#include <vector>
#include <cstddef> // for size_t
#include <cstdint> // for int64_t


//
// functionally the same as std::snprintf but also asserts that the result is non-negative and less than size
//
// returns the number of characters written, not counting the terminating null character.
//
size_t SNPRINTF(char *dest, size_t size, const char *format, ...);


std::vector<std::string> split(const std::string &s, char delim);

std::string escape(const std::string &s);

[[nodiscard]] Status parseInt(const std::string &str, int *out);

[[nodiscard]] Status parseInt64(const std::string &str, int64_t *out);

[[nodiscard]] Status parseInt64(const char *str, int64_t *out);

[[nodiscard]] Status parseSizeT(const std::string &str, size_t *out);

[[nodiscard]] Status parseUInt16(const std::string &str, uint16_t *out);
















