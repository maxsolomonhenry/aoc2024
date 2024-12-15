#include <iostream>
#include <sstream>
#include "../common/util.h"

enum Trend {
    UP,
    DOWN,
    NUL
};

bool isSafe(const std::string &line){

    std::stringstream ss(line);
    std::string token;
    int val;
    int diff;
    Trend trend = NUL;

    // Grab first value.
    ss >> token;
    val = std::stoi(token);

    while (ss >> token)
    {
        diff = val - std::stoi(token);

        if ((std::abs(diff) > 3) || (std::abs(diff) < 1))
            return false;

        switch(trend) {
            case Trend::UP:
                if (diff < 0)
                    return false;
                break;
            case Trend::DOWN:
                if (diff > 0)
                    return false;
                break;
            case Trend::NUL:
                if (diff > 0)
                    trend = Trend::UP;

                if (diff < 0)
                    trend = Trend::DOWN;
                break;
        }

        val = std::stoi(token);
    }

    return true;
}

int main() {
    std::vector<std::string> lines = util::read("../src/day02/input.txt");

    int nSafe = 0;

    for (const auto &line : lines)
    {
        if (isSafe(line))
            nSafe += 1;
    }

    std::cout << "Number of safe reports: " << nSafe << "\n";

    return 0;
}