#include "../common/util.h"

#include <iostream>
#include <unordered_set>

long long concatenate(long long prev, long long operand) {
    return std::stol(std::to_string(prev) + std::to_string(operand));
}

long long evaluate(std::string line) {
    auto values = util::parseLongs(line, ' ');
    
    // Pop off first element.
    long long target = values[0];
    values.erase(values.begin());

    std::unordered_set<long long> dp;
    dp.insert(values[0]);

    for (int i = 1; i < values.size(); i++)
    {
        std::unordered_set<long long> next;
        long long operand = values[i];
        for (long long prev : dp) 
        {
            next.insert(prev + operand);
            next.insert(prev * operand);
            next.insert(concatenate(prev, operand));
        }

        dp = std::move(next);
    }

    if (dp.count(target) > 0)
    {
        return target;
    }

    return 0;
}

int main() {
    auto lines = util::read("src/day07/input.txt");

    long long score = 0;
    for (auto line : lines)
    {
        score += evaluate(line);
    }

    std::cout << "Final score: " << score << "\n";
}