
#include "common/clock.h"
#include "common/logging.h"

#include "gtest/gtest.h"

#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::seconds


#define TAG "ClockTest"


class ClockTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {

        // SetLogLevel(LOGLEVEL_TRACE);
        SetLogLevel(LOGLEVEL_INFO);
        // SetLogLevel(LOGLEVEL_ERROR);
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

TEST_F(ClockTest, wallClockSeconds) {

    int64_t start = wallClockSeconds();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    int64_t end = wallClockSeconds();

    int64_t diff = end - start;

    EXPECT_GT(diff, 1);
    EXPECT_LT(diff, 4);
}
















