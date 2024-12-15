#include "../common/util.h"

#include <iostream>
#include <cctype>

int parseLine(std::string line) {
    std::string buffer = "";
    static const std::string kPattern = "mul(#,#)";
    int pRead = 0;
    int nDigits = 0;

    for (const auto &c : line)
    {
        char target = kPattern[pRead];

        if (target == '#') {
            nDigits++;
            if (!std::isdigit(c) || nDigits > 3) {
                buffer.clear();
                pRead = 0;
                nDigits = 0;
                continue;
            }

            buffer += c;
            std::cout << buffer << '\n';

        } else if (c == target) {
            buffer += c;
            pRead++;
            std::cout << buffer << '\n';

        } else {
            buffer.clear();
            pRead = 0;
            nDigits = 0;
        }
        
    }

    return 0;
}

int main() {
    std::vector<std::string> lines = util::read("src/day03/input.txt");

    if (lines.empty())
        return 1;

    int score = 0;
    for (const auto &line : lines)
        score += parseLine(line);

    return 0;
}