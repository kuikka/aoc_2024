#include <fstream>
#include <ios>

#include "parser.hpp"



int main(int argc, char *argv[])
{
    Parser p;
    std::vector<std::tuple<int, int>> outputs;
    std::ifstream f(argv[1]);

    while (!f.eof())
    {
        char c;
        f.get(c);
        std::cout << c;
        auto output = p.input(c);
        if (output.has_value()) {
            outputs.push_back(output.value());
        }

    }

    // for (char c : test_input) {
    //     auto output = p.input(c);
    //     if (output.has_value()) {
    //         outputs.push_back(output.value());
    //     }
    // }

    int sum = 0;
    for (auto& t: outputs)
    {
        int m = std::get<0>(t) * std::get<1>(t);
        sum += m;
    }
    std::cout << "Sum: " << sum << std::endl;
}