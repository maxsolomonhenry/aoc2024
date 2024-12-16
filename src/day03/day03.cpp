#include "../common/util.h"

#include <iostream>
#include <cctype>
#include <regex>

int parseLine(std::string line) {
    static const std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::sregex_iterator it(line.begin(), line.end(), pattern);
    std::sregex_iterator end;

    int sum = 0;
    while (it != end) {
        std::smatch match = *it;
        sum += std::stoi(match[1].str()) * std::stoi(match[2].str());
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