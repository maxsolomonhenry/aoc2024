#include "../common/util.h"

#include <iostream>

int main() {
    const auto& lines = util::read("src/day09/input.txt");

    std::vector<int> nBlocks;
    std::vector<int> nEmpty;

    for (int i = 0; i < lines[0].size(); i++)
    {
        if (i % 2 == 0)
            nBlocks.push_back(util::ctoi(lines[0][i]));
        else
            nEmpty.push_back(util::ctoi(lines[0][i]));
    }

    

    return 0;
}