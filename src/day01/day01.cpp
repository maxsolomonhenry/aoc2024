#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "../common/util.h"

int main() {

    std::string fpath = "../src/day01/input.txt";
    std::vector<std::string> lines = util::read(fpath);

    std::vector<int> left;
    std::vector<int> right;

    for (std::string line : lines) {
        std::stringstream ss(line);
        std::string token;

        ss >> token;
        left.push_back(std::stoi(token));

        ss >> token;
        right.push_back(std::stoi(token));
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int total = 0;
    std::unordered_map<int, int> counts;
    for (size_t i = 0; i < left.size(); i++) {
        // Part 1.
        total += std::abs(left[i] - right[i]);

        // Part 2.
        counts[right[i]] += 1;
    }

    int similarity = 0;
    for (size_t i = 0; i < left.size(); i++) {
        similarity += left[i] * counts[left[i]];
    }

    std::cout << "Total: " << total << '\n';
    std::cout << "Similarity: " << similarity << '\n';

    return 0;
}