#include "../common/util.h"

#include <iostream>
#include <unordered_set>

int evaluate(std::string line) {
    auto values = util::parseLongs(line, ' ');
    
    // Pop off first element.
    long target = values[0];
    values.erase(values.begin());

    std::unordered_set<long> dp;
    dp.insert(values[0]);

    for (int i = 1; i < values.size(); i++)
    {
        std::unordered_set<long> next;
        long operand = values[i];
        for (long prev : dp) 
        {
            // std::cout << prev << ", ";
            next.insert(prev + operand);
            next.insert(prev * operand);
        }
        // std::cout << "| ";

        dp = std::move(next);
    }

    // for (auto element : dp) {
    //     std::cout << element << ", ";
    // }

    if (dp.count(target) > 0)
    {
        // std::cout << "Success.\n";
        return target;
    }

    // std::cout << "Failure.\n";
    return 0;
}

int main() {
    auto lines = util::read("src/day07/input.txt");

    long score = 0;
    for (auto line : lines)
    {
        score += evaluate(line);
    }

    std::cout << "Final score: " << score << "\n";
}