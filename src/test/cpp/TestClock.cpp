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

#include "common/clock.h"
#include "common/logging.h"

#include "gtest/gtest.h"

#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::seconds
#include <locale>


#define TAG "ClockTest"


class ClockTest : public ::testing::Test {
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


TEST_F(ClockTest, uptimeMillis) {

    int64_t start = uptimeMillis();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    int64_t end = uptimeMillis();

    int64_t diff = end - start;

    EXPECT_GT(diff, 0);
    EXPECT_LT(diff, 1000);
}

TEST_F(ClockTest, timeSinceEpoch) {

    int64_t start = timeSinceEpochSeconds();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    int64_t end = timeSinceEpochSeconds();

    int64_t diff = end - start;

    EXPECT_GT(diff, 1);
    EXPECT_LT(diff, 4);
}

TEST_F(ClockTest, formatTime) {

    //
    // test using a different locale that would print wider than allowed
    //
    std::setlocale(LC_TIME, "ja_JP");

    char buf[FORMATTIME_LEN + 1];

    time_t timer;
    if (std::time(&timer) == -1) {
        FAIL();
    }

    formatTime(timer, buf, sizeof(buf));

    LOGI("formatTime: buf: %s", buf);
}
















