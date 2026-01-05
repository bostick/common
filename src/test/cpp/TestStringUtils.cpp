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

#include "common/logging.h"
#include "common/string_utils.h"

#include "gtest/gtest.h"


#define TAG "StringUtilsTest"


using enum Status;


class StringUtilsTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {

//        SetLogLevel(LOGLEVEL_TRACE);
        SetLogLevel(LOGLEVEL_INFO);
//        SetLogLevel(LOGLEVEL_ERROR);
    }
    
    static void TearDownTestSuite() {
        
    }
    
    void SetUp() override {
        
    }
    
    void TearDown() override {

    }
};


TEST_F(StringUtilsTest, parseInt) {
    
    std::string str = "123";
    int out;
    
    Status status;
    status = parseInt(str, &out);
    
    EXPECT_EQ(status, OK);
    
    EXPECT_EQ(out, 123);
    
    str = "123.456";
    status = parseInt(str, &out);
    
    EXPECT_EQ(status, ERR);
}


TEST_F(StringUtilsTest, parseInt64) {

    std::string str = "123";
    int64_t out;
    
    Status status;
    status = parseInt64(str, &out);
    
    EXPECT_EQ(status, OK);
    
    EXPECT_EQ(out, 123);
    
    str = "123.456";
    status = parseInt64(str, &out);
    
    EXPECT_EQ(status, ERR);
}


TEST_F(StringUtilsTest, parseSizeT) {

    std::string str = "123";
    size_t out;
    
    Status status;
    status = parseSizeT(str, &out);
    
    EXPECT_EQ(status, OK);
    
    EXPECT_EQ(out, 123);
    
    str = "123.456";
    status = parseSizeT(str, &out);
    
    EXPECT_EQ(status, ERR);
}


TEST_F(StringUtilsTest, parseUInt16) {

    std::string str = "123";
    uint16_t out;
    
    Status status;
    status = parseUInt16(str, &out);
    
    EXPECT_EQ(status, OK);
    
    EXPECT_EQ(out, 123);
    
    str = "123.456";
    status = parseUInt16(str, &out);
    
    EXPECT_EQ(status, ERR);
}
















