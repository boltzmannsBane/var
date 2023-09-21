#include <gtest/gtest.h>

// Simple function to test
int add(int a, int b) {
    return a + b;
}

// Test case
TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(3, add(1, 2));
    EXPECT_EQ(5, add(3, 2));
}

TEST(AdditionTest, HandlesNegativeInput) {
    EXPECT_EQ(-3, add(-1, -2));
    EXPECT_EQ(1, add(3, -2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
