#pragma once

#include <tuple>
#include <optional>
#include <vector>
#include <string>
#include <iostream>

#include <fmt/format.h>

#define DEBUG 0

class Parser
{
    enum state {
        PREFIX,
        FIRST_NUMBER,
        // COMMA,
        SECOND_NUMBER,
        CLOSING_PAREN,
    };
    enum state state = state::PREFIX; // What to expect next
    bool enabled = true;
    std::string prefix;
    std::string first_number;
    std::string second_number;

    void reset() {
        state = state::PREFIX;
        prefix.clear();
        first_number.clear();
        second_number.clear();
    }

    bool expect(char expected_char, char c)
    {
        if (c == expected_char) {
            return true;
        }
        return false;
    }

    std::string last(size_t n)
    {
        auto len = prefix.length();

        if (n > len)
            return "";

        return prefix.substr(len - n);
    }

    void match_prefix()
    {
        if (DEBUG)
            fmt::print("prefix: {}\n", prefix);

        if (last(3) == "mul") {
            prefix = "mul";
            state = state::FIRST_NUMBER;
        }
        else if (last(2) == "do") {
            prefix = "do";
            state = state::CLOSING_PAREN;
        }
        else if (last(5) == "don't") {
            prefix = "don't";
            state = state::CLOSING_PAREN;
        }
        else {
            reset();
        }
    }

    void finish()
    {
        if (prefix == "do") {
            enabled = true;
        } else if (prefix == "don't") {
            enabled = false;
        }
        reset();
    }

public:
    std::optional<std::tuple<int, int>> input(char c) {
        if (DEBUG)
            fmt::print("state={}, got={}\n", (int)state, c);
        switch (state)
        {
            case state::PREFIX:
                if (expect('(', c)) {
                    match_prefix();
                }
                else {
                    prefix += c;
                }
                break;

            case state::CLOSING_PAREN:
                if (expect(')', c)) {
                    finish();
                } else {
                    reset();
                }
                break;

            case state::FIRST_NUMBER:
                if (std::isdigit(c)) {
                    first_number += c;
                } else if (expect(',', c)) {
                    state = state::SECOND_NUMBER;
                } else {
                    reset();
                }
                break;

            case state::SECOND_NUMBER:
                if (std::isdigit(c)) {
                    second_number += c;
                } else if (expect(')', c)) {
                    // std::cout << "Got " << first_number << "," << second_number << std::endl;
                    auto ret = std::make_tuple(std::stoi(first_number), std::stoi(second_number));
                    reset();
                    if (enabled) {
                        return ret;
                    } else {
                        return {};
                    }
                } else {
                    reset();
                }
                break;
        }
        return {};
    }
};