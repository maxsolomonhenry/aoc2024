#include <iostream>
#include <sstream>
#include "../common/util.h"

enum Trend {
    UP,
    DOWN,
    NONE
};

bool isSafe(const std::string &line, const int &nMaxErrors){

    std::stringstream ss(line);
    std::string token;
    int val;
    int diff;
    Trend trend = NONE;

    // Grab first value.
    ss >> token;
    val = std::stoi(token);

    int nErrors = 0;
    while (ss >> token)
    {
        diff = val - std::stoi(token);

        if ((std::abs(diff) > 3) || (std::abs(diff) < 1))
            nErrors++;

        switch(trend) {
            case Trend::UP:
                if (diff < 0)
                    nErrors++;
                break;
            case Trend::DOWN:
                if (diff > 0)
                    nErrors++;
                break;
            case Trend::NONE:
                if (diff > 0)
                    trend = Trend::UP;

                if (diff < 0)
                    trend = Trend::DOWN;
                break;
        }

        val = std::stoi(token);
    }

    return nErrors <= nMaxErrors;
}

int main() {
    std::vector<std::string> lines = util::read("src/day02/input.txt");

    if (lines.empty())
        return 1;

    int nSafePart1 = 0;
    int nSafePart2 = 0;

    for (const auto &line : lines)
    {
        if (isSafe(line, 0))
            nSafePart1++;

        if (isSafe(line, 1))
            nSafePart2++;
    }

    std::cout << "Number of safe reports (Part 1): " << nSafePart1 << "\n";
    std::cout << "Number of safe reports (Part 2): " << nSafePart2 << "\n";

    return 0;
}