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

#include "common/string_utils.h"

#undef NDEBUG

#include "common/assert.h"
#include "common/error.h"
#include "common/logging.h"

#include <sstream>
#include <cstdlib> // for strtoll
#include <cstring> // for strerror


#define TAG "string_utils"


std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

std::string escape(std::string s) {

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

        *out = std::stoi(str);

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
    
    static_assert(sizeof(long long) == sizeof(int64_t));
    
    ASSERT(!str.empty());

    try {

        *out = std::stoll(str);

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
    
    static_assert(sizeof(long long) == sizeof(int64_t));

    ASSERT(str != NULL);
    ASSERT(*str != '\0');

    //
    // https://man7.org/linux/man-pages/man3/strtol.3.html#CAVEATS
    //
    errno = 0;

    *out = std::strtoll(str, NULL, 10);

    if (errno != 0) {
        LOGE("strtoll: %s %s", ErrorName(errno), ERRORSTRING(errno));
        return ERR;
    }

    return OK;
}
















