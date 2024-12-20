#pragma once

#include <tuple>
#include <optional>
#include <vector>
#include <string>
#include <iostream>

class Parser
{
    enum state {
        M,
        U,
        L,
        OPEN_PAREN,
        FIRST_NUMBER,
        // COMMA,
        SECOND_NUMBER,
        // CLOSING_PAREN,
    };
    enum state state = state::M; // What to expect next
    std::string first_number;
    std::string second_number;

    void reset() {
        state = state::M;
        first_number.clear();
        second_number.clear();
    }

    bool expect(char expected_char, char c)
    {
        if (c == expected_char) {
            return true;
        }
        reset();
        return false;
    }

public:
    std::optional<std::tuple<int, int>> input(char c) {
        // std::cout << "Got " << c << std::endl;
        switch (state)
        {
            case state::M:
                if (expect('m', c)) {
                    state = state::U;
                }
                break;
            case state::U:
                if (expect('u', c)) {
                    state = state::L;
                }
                break;
            case state::L:
                if (expect('l', c)) {
                    state = state::OPEN_PAREN;
                }
                break;
            case state::OPEN_PAREN:
                if (expect('(', c)) {
                    state = state::FIRST_NUMBER;
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
                    return ret;
                } else {
                    reset();
                }
            
                break;
        }
        return {};
    }
};