#include <gtest/gtest.h>
#include "mylib/mylib.hpp"

namespace {

class MylibTest : public ::testing::Test {
protected:
    // Setup/Teardown if needed
};

TEST_F(MylibTest, AddPositive) {
    EXPECT_EQ(mylib::add(2, 3), 5);
}

TEST_F(MylibTest, AddNegative) {
    EXPECT_EQ(mylib::add(-2, -3), -5);
}

TEST_F(MylibTest, AddMixed) {
    EXPECT_EQ(mylib::add(5, -3), 2);
}

TEST_F(MylibTest, MultiplyPositive) {
    EXPECT_EQ(mylib::multiply(3, 4), 12);
}

TEST_F(MylibTest, MultiplyWithZero) {
    EXPECT_EQ(mylib::multiply(5, 0), 0);
}

TEST_F(MylibTest, MultiplyNegative) {
    EXPECT_EQ(mylib::multiply(-3, 4), -12);
    EXPECT_EQ(mylib::multiply(-3, -4), 12);
}

}  // namespace
