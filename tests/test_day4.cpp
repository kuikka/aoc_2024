#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include <fmt/format.h>

class XMasFinder
{
    const std::vector<std::string> input;
    int width = 0;
    int height = 0;
    const std::string xmas = "XMAS";
    int found = 0;

public:
    XMasFinder(const std::vector<std::string> input) : input(input) {
        width = input[0].length();
        height = input.size();
    };

    int findXMas()
    {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                checkAll(x, y);
            }
        }
        return found;
    }

    void checkAll(int x, int y)
    {
        if (get(x, y) == xmas[0]) {
            check(x, y, 1, 0);
            check(x, y, -1, 0);
            check(x, y, 0, 1);
            check(x, y, 0, -1);
            check(x, y, 1, 1);
            check(x, y, -1, -1);
            check(x, y, 1, -1);
            check(x, y, -1, 1);
        }
    }

    void check(int x, int y, int deltaX, int deltaY)
    {
        for (size_t i = 0; i < xmas.length(); i++)
        {
            if (get(x + i * deltaX, y + i * deltaY) != xmas[i])
            {
                return;
            }
        }
        found++;
    }

    int get(int x, int y)
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            return input[y][x];
        }
        return ' ';
    }
};


std::vector<std::string> readInput(const char *filename)
{
    std::vector<std::string> ret;
    std::ifstream f(filename);
    EXPECT_EQ(f.good(), true);

    std::string line;
    while (std::getline(f, line))
    {
        ret.push_back(line);
    }
    return ret;
}

TEST(Day4Tests, input_1)
{
    std::vector<std::string> input = {
        "MMMSXXMASM",
        "MSAMXMSMSA",
        "AMXSXMAAMM",
        "MSAMASMSMX",
        "XMASAMXAMM",
        "XXAMMXXAMA",
        "SMSMSASXSS",
        "SAXAMASAAA",
        "MAMMMXMMMM",
        "MXMXAXMASX",
    };

    XMasFinder finder(input);
    int count = finder.findXMas();
    EXPECT_EQ(count, 18);
}

TEST(Day4Tests, input_two)
{
    std::vector<std::string> input = readInput("projects/aoc_2024/inputs/day4.txt");

    XMasFinder finder(input);
    int count = finder.findXMas();
    EXPECT_EQ(count, 2571);
}