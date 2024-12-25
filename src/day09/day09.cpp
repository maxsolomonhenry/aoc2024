#include "../common/util.h"

#include <unordered_map>
#include <iostream>
#include <utility>

using block = std::pair<int, int>;

int main() {


    const auto& lines = util::read("src/day09/input.txt");

    std::unordered_map<int, block> memory;

    int fileNo = 0;
    for (int i = 0; i < lines[0].size(); i++)
    {
        if (i % 2 == 0)
            memory[i] = block(fileNo++, util::ctoi(lines[0][i]));
        else
            memory[i] = block(-1, util::ctoi(lines[0][i]));
    }

    return 0;
}