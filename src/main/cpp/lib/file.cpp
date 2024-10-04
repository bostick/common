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

#include "common/file.h"

#include "common/check.h"
#include "common/logging.h"
#include "common/platform.h"

#include <cstdio>


#if IS_PLATFORM_WINDOWS
#define _CRT_SECURE_NO_DEPRECATE // disable warnings about fopen being insecure on MSVC
#endif // IS_PLATFORM_WINDOWS


#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"


#define TAG "file"


//
// use fopen and friends
//
Status
openFile(
  const char *path,
  std::vector<uint8_t> &out) {
  
  FILE *file = std::fopen(path, "rb");

  CHECK(file, "cannot open %s", path);

  int fres = std::fseek(file, 0, SEEK_END);
  
  CHECK_NOT(fres, "fseek failed");

  long res = std::ftell(file);

  CHECK_NOT(res < 0, "ftell failed");

  auto len = static_cast<size_t>(res);

  std::rewind(file);

  out = std::vector<uint8_t>(len);

  size_t r = std::fread(out.data(), sizeof(uint8_t), len, file);

  CHECK(r == len, "fread failed");

  fres = std::fclose(file);

  CHECK_NOT(fres, "fclose failed");

  return OK;
}


//
// use fopen and friends
//
Status
saveFile(
  const char *path,
  const std::vector<uint8_t> &buf) {

  FILE *file = std::fopen(path, "wb");

  CHECK(file, "cannot open %s", path);

  auto r = std::fwrite(buf.data(), sizeof(uint8_t), buf.size(), file);

  CHECK(r == buf.size(), "fwrite failed");

  int fres = std::fclose(file);

  CHECK_NOT(fres, "fclose failed");

  return OK;
}


bool fileExists(const char *path) {

  FILE *file = std::fopen(path, "r");

  if (file == NULL) {
    //
    // file does NOT exist
    //
    return false;
  }

  //
  // file DOES exist
  //

  std::fclose(file);

  return true;
}


#pragma clang diagnostic pop










