#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include "parser.hpp"

std::string test_input = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

namespace {
    int sum_input(const std::string& input) {
        std::vector<std::tuple<int, int>> outputs;
        Parser p;

        for (char c : input) {
            auto output = p.input(c);
            if (output.has_value()) {
                outputs.push_back(output.value());
            }
        }
        int sum = 0;
        for (auto& t: outputs)
        {
            int m = std::get<0>(t) * std::get<1>(t);
            sum += m;
        }
        return sum;
    }
};

TEST(Day3Test, test_input1)
{
    int sum = sum_input(test_input);
    EXPECT_EQ(sum, 161);
}

TEST(Day3Test, test_input2)
{
    std::ifstream t("projects/aoc_2024/inputs/day3.txt");

    ASSERT_EQ(t.good(), true);
    std::stringstream buffer;
    buffer << t.rdbuf();

    int sum = sum_input(buffer.str());
    EXPECT_EQ(sum, 174336360);
}