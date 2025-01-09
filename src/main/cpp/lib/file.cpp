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

#include "common/platform.h"

#if IS_PLATFORM_WINDOWS
#define _CRT_SECURE_NO_DEPRECATE // disable warnings about fopen being insecure on MSVC
#endif // IS_PLATFORM_WINDOWS

#include "common/file.h"

#include "common/check.h"
#include "common/error.h"
#include "common/logging.h"
#include "common/status.h"

#include <filesystem>
#include <cstring> // for strerror


#define TAG "file"


//
// use fopen and friends
//
Status
openFile(
    const char *path,
    std::vector<uint8_t> &out) {

    ScopedFile x{path, "rb"};

    FILE *file = x.get();

    CHECK(file, "cannot open %s", path);

    int fres = std::fseek(file, 0, SEEK_END);

    CHECK_NOT(fres, "fseek failed: %s %s", ErrorName(errno), std::strerror(errno));

    long res = std::ftell(file);

    CHECK_NOT(res < 0, "ftell failed: %s %s", ErrorName(errno), std::strerror(errno));

    auto len = static_cast<size_t>(res);

    std::rewind(file);

    out = std::vector<uint8_t>(len);

    size_t r = std::fread(out.data(), sizeof(uint8_t), len, file);

    //
    // fread does not distinguish between end-of-file and error, and callers must use feof and ferror to determine which occurred.
    //

    if (r != len) {

        if (std::feof(file)) {
            LOGE("fread failed: unexpected end of file");
        } else if (std::ferror(file)) {
            LOGE("fread failed: error reading file");
        }

        return ERR;
    }

    return OK;
}


//
// use fopen and friends
//
Status
saveFile(
    const char *path,
    const std::vector<uint8_t> &buf) {

    ScopedFile x{path, "wb"};

    FILE *file = x.get();

    CHECK(file, "cannot open %s", path);

    auto r = std::fwrite(buf.data(), sizeof(uint8_t), buf.size(), file);

    CHECK(r == buf.size(), "fwrite failed: %s %s", ErrorName(errno), std::strerror(errno));

    return OK;
}


bool fileExists(const char *path) {

    ScopedFile x{path, "r"};

    FILE *file = x.get();

    return (file != NULL);
}


Status createDirectory(const char *path) {

    if (directoryExists(path)) {
        return OK;
    }

    std::error_code ec;

    if (std::filesystem::create_directories(path, ec)) {
        return OK;
    }

    LOGE("error creating directory %s: %s", path, ec.message().c_str());

    return ERR;
}


bool directoryExists(const char *path) {
    return std::filesystem::is_directory(path);
}


Status
deleteFile(const char *path) {

    std::error_code ec;

    if (std::filesystem::remove(path, ec)) {
        return OK;
    }

    LOGE("error deleting file %s: %s", path, ec.message().c_str());

    return ERR;
}


Status
deleteFileIfPresent(const char *path) {

    if (!fileExists(path)) {
        return OK;
    }
    
    std::error_code ec;

    if (!std::filesystem::remove(path, ec)) {
        LOGE("error deleting file %s: %s", path, ec.message().c_str());
        return ERR;
    }

    return OK;
}


Status
deleteEmptyDirectory(const char *path) {

    std::error_code ec;

    if (std::filesystem::remove(path, ec)) {
        return OK;
    }

    LOGE("error deleting empty directory %s: %s", path, ec.message().c_str());

    return ERR;
}

Status
deleteEmptyDirectoryIfPresent(const char *path) {

    if (!directoryExists(path)) {
        return OK;
    }
    
    std::error_code ec;

    if (!std::filesystem::remove(path, ec)) {
        LOGE("error deleting empty directory %s: %s", path, ec.message().c_str());
        return ERR;
    }

    return OK;
}


ScopedFile::ScopedFile(const char *path, const char *mode) :
    file() {

    file = std::fopen(path, mode);

    if (file == NULL) {
        LOGE("cannot open %s: %s %s", path, ErrorName(errno), std::strerror(errno));
        return;
    }
}

ScopedFile::~ScopedFile() {

    if (file == NULL) {
        return;
    }

    if (std::fclose(file) != 0) {
        LOGE("fclose failed");
    }
}

FILE *ScopedFile::get() {
    return file;
}
















