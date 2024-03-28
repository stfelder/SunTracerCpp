#include "gtest/gtest.h"
#include "Calculator.h"

TEST(SumTest, TwoNumbers) {
    Calculator calculator;
    int num1 = 5;
    int num2 = 7;
    EXPECT_EQ(calculator.summe<int>(num1, num2), 12);
}


TEST(SumTest, TwoNumbers_Doubles) {
    Calculator calculator;
    double num1 = 5;
    double num2 = 7;
    EXPECT_EQ(calculator.summe<double>(num1, num2), num1 + num2);
}