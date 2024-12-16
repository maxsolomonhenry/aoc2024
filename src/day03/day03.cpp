#include "../common/util.h"

#include <iostream>
#include <cctype>
#include <regex>

int parseLine(std::string line) {
    static const std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
    std::sregex_iterator it(line.begin(), line.end(), pattern);
    std::sregex_iterator end;

    int sum = 0;
    bool doGate = true;

    while (it != end) {
        std::smatch match = *it;

        if (match[1].matched) {
            sum += std::stoi(match[1].str()) * std::stoi(match[2].str()) * doGate;
        } else {
            doGate = (match[0] == "do()");
        }
        ++it;
    }

    return sum;
}

int main() {
    std::vector<std::string> lines = util::read("src/day03/input.txt");

    if (lines.empty())
        return 1;

    int score = 0;
    for (const auto &line : lines)
        score += parseLine(line);

    std::cout << "Total output: " << score << '\n';

    return 0;
}