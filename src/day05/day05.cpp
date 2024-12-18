#include "../common/util.h"

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>

bool isInOrder(const std::vector<int> values, std::unordered_map<int, std::vector<int>> &order) {
    int key = -1;

    for (auto val : values)
    {

        if (key == -1)
        {
            key = val; 
            continue;
        }

        if (!util::contains(order[key], val))
            return false;
            
        key = val;
    }

    return true;
}

void reorder(std::vector<int> &values, std::unordered_map<int, std::vector<int>> &order) {
    
    int nRight = 0;
    while (nRight < values.size() - 1)
    {
        nRight = 0;
        for (int i = 0; i < values.size() - 1; i++) 
        {
            int key = values[i];
            int val = values[i + 1];

            if (util::contains(order[key], val))
                nRight++;
            else
                std::swap(values[i], values[i+1]);


            // for (auto element : values)
            //     std::cout << element << " ";
            // std::cout << ": " << key << "|" << val << "\n";

            key = val;
        }
    }
}

int main() {

    const auto lines = util::read("src/day05/input.txt");

    bool isFirstHalf = true;
    std::unordered_map<int, std::vector<int>> order;

    int totalOrdered = 0;
    int totalUnordered = 0;
    for (auto &line : lines)
    {
        if (line == "")
        {
            isFirstHalf = false;
            continue;
        }

        if (isFirstHalf)
        {
            int first, second;
            char delimiter;
            std::stringstream ss(line);

            // Parse numbers in pattern "#|#".
            ss >> first >> delimiter >> second;
            
            order[first].push_back(second);
            continue;
        }

        auto values = util::parseIntegers(line, ',');
        if (isInOrder(values, order))
            totalOrdered += values[values.size() / 2];
        else
        {
            reorder(values, order);
            totalUnordered += values[values.size() / 2];
        }
    }

    std::cout << "Total ordered: " << totalOrdered << "\n";
    std::cout << "Total unordered: " << totalUnordered << "\n";
    return 0;
}