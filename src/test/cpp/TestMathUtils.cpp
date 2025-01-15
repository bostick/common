
#include "common/logging.h"
#include "common/math_utils.h"

#include "gtest/gtest.h"


#define TAG "MathUtilsTest"


class MathUtilsTest : public ::testing::Test {
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


TEST_F(MathUtilsTest, euclidean_mod) {

   EXPECT_EQ(-11 % 5, -1);

   EXPECT_EQ(euclidean_mod((int8_t)-11, 5), 4);
}
















