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

#include <vector>
#include <cstdint> // for uint8_t
#include <cstdio> // for FILE


//
// open file and read contents into out buffer
//
Status
openFile(const char *path,
         std::vector<uint8_t> &out);

//
// save buf to file
//
Status
saveFile(const char *path,
         const std::vector<uint8_t> &buf);

//
// if file exists, then return true
//
bool fileExists(const char *path);

//
//
//
Status
createDirectory(const char *path);

//
//
//
bool directoryExists(const char *path);

//
//
//
Status
deleteFile(const char *path);

//
//
//
Status
deleteFileIfPresent(const char *path);

//
//
//
Status
deleteEmptyDirectory(const char *path);

//
//
//
Status
deleteEmptyDirectoryIfPresent(const char *path);


class ScopedFile {
private:

    FILE *file;

public:

    ScopedFile(const char *path, const char *mode);

    ~ScopedFile();

    FILE *get();
};
















