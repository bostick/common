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
#define _CRT_SECURE_NO_WARNINGS // disable warnings about strerror being insecure on MSVC
#endif // _MSC_VER

#include "common/string_utils.h"

#undef NDEBUG

#include "common/abort.h"
#include "common/assert.h"
#include "common/error.h"
#include "common/logging.h"

#include <limits>
#include <sstream>
#include <cstdlib> // for strtoll
#include <cstring> // for strerror
#include <cstdio> // for vsnprintf
#include <cstdarg> // for va_list


#define TAG "string_utils"


using enum Status;


std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

std::string escape(const std::string &s) {

    std::string newString;
    for (auto it = s.begin(); it < s.end(); it++) {
        auto c = *it;
        if (c == '\n') {
            newString += "\\n";
        }
        else {
            newString += c;
        }
    }

    return newString;
}

Status parseInt(const std::string &str, int *out) {

    ASSERT(!str.empty());

    try {

        size_t pos; // number of characters processed NOLINT(*-init-variables)
        *out = std::stoi(str, &pos);

        if (pos != str.size()) {
            LOGE("stoi: did not process all characters in string");
            return ERR;
        }

        return OK;

    } catch (const std::invalid_argument &ex) {

        LOGE("stoi: %s", ex.what());
        return ERR;

    } catch (const std::out_of_range &ex) {

        LOGE("stoi: %s", ex.what());
        return ERR;
    }
}


Status parseInt64(const std::string &str, int64_t *out) {

    static_assert(sizeof(int64_t) == sizeof(long long)); // NOLINT(google-runtime-int)
    
    ASSERT(!str.empty());

    try {

        size_t pos; // number of characters processed NOLINT(*-init-variables)
        *out = std::stoll(str, &pos);

        if (pos != str.size()) {
            LOGE("stoll: did not process all characters in string");
            return ERR;
        }

        return OK;

    } catch (const std::invalid_argument &ex) {

        LOGE("stoll: %s", ex.what());
        return ERR;

    } catch (const std::out_of_range &ex) {

        LOGE("stoll: %s", ex.what());
        return ERR;
    }
}

Status parseInt64(const char *str, int64_t *out) {

    static_assert(sizeof(int64_t) == sizeof(long long)); // NOLINT(google-runtime-int)

    ASSERT(str != nullptr);
    ASSERT(*str != '\0');

    size_t len = std::strlen(str);

    //
    // https://man7.org/linux/man-pages/man3/strtol.3.html#CAVEATS
    //
    errno = 0;

    char *c; // last character that was converted NOLINT(*-init-variables)
    *out = std::strtoll(str, &c, 10);

    if (errno != 0) {
        LOGE("strtoll: %s (%s)", std::strerror(errno), ErrorName(errno));
        return ERR;
    }

    if (c != str + len) {
        LOGE("strtoll: did not process all characters in string");
        return ERR;
    }

    return OK;
}


Status parseSizeT(const std::string &str, size_t *out) {

    ASSERT(!str.empty());

    errno = 0;

    //
    // incorrect warning "Condition is always true"
    //
    if constexpr (sizeof(size_t) == sizeof(unsigned long)) { // NOLINT(google-runtime-int)

        char *c; // last character that was converted NOLINT(*-init-variables)
        *out = std::strtoul(str.c_str(), &c, 10);

        if (errno != 0) {
            LOGE("strtoul: %s (%s)", std::strerror(errno), ErrorName(errno));
            return ERR;
        }

        if (c != str.c_str() + str.size()) {
            LOGE("strtoul: did not process all characters in string");
            return ERR;
        }

        return OK;

        //
        // incorrect warning "Condition is always true"
        //
    } else if constexpr (sizeof(size_t) == sizeof(unsigned long long)) { // NOLINT(google-runtime-int)

        char *c; // last character that was converted NOLINT(*-init-variables)
        *out = std::strtoull(str.c_str(), &c, 10);

        if (errno != 0) {
            LOGE("strtoull: %s (%s)", std::strerror(errno), ErrorName(errno));
            return ERR;
        }

        if (c != str.c_str() + str.size()) {
            LOGE("strtoull: did not process all characters in string");
            return ERR;
        }

        return OK;

    } else {
        ABORT("sizeof(size_t) is unrecognized: %zu", sizeof(size_t));
    }
}


Status parseUInt16(const std::string &str, uint16_t *out) {

    ASSERT(!str.empty());

    errno = 0;

    char *c; // last character that was converted NOLINT(*-init-variables)
    auto a = std::strtoul(str.c_str(), &c, 10);

    if (errno != 0) {
        LOGE("strtoul: %s (%s)", std::strerror(errno), ErrorName(errno));
        return ERR;
    }

    if (c != str.c_str() + str.size()) {
        LOGE("strtoul: did not process all characters in string");
        return ERR;
    }

    if (std::numeric_limits<uint16_t>::max() < a) {
        LOGE("value is greater than can be represented by uint16_t: %lu", a);
        return ERR;
    }

    *out = static_cast<uint16_t>(a);

    return OK;
}


size_t SNPRINTF(char *dest, size_t size, const char *format, ...) {

    va_list args; // NOLINT(*-init-variables)
    va_start(args, format);
    int res; // NOLINT(*-init-variables)
    res = std::vsnprintf(dest, size, format, args);
    va_end(args);

    ASSERT(res >= 0);
    ASSERT(res < static_cast<int>(size)); // incorrect warning: comparison between 'signed' and 'unsigned' integers

    return static_cast<size_t>(res);
}


Status STRNCPY(char *dest, const char *src, size_t len) {

    std::strncpy(dest, src, len);

    //
    // Because strncpy() does not guarantee to NUL terminate the string itself,
    // this must be done explicitly.
    //
    if (dest[len - 1] != '\0') {
        return ERR;
    }

    return OK;
}
















