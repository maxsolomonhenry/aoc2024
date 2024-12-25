#include "../common/util.h"
#include "../common/point.h"

#include <iostream>
#include <unordered_map>
#include <unordered_set>

bool isInBounds(Point point, int width, int height) {
    return (point.x >= 0 && point.x < width && point.y >= 0 && point.y < height);
}

int main() {
    auto lines = util::read("src/day08/input.txt");

    std::unordered_map<char, std::vector<Point>> antennae;

    const int width = lines[0].size();
    const int height = lines.size();

    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            if (lines[y][x] != '.')
                antennae[lines[y][x]].push_back(Point(x, y));

    std::unordered_set<Point> antinodes;
    for (const auto& [label, positions] : antennae)
    {
        for (const Point& anchor : positions) 
            for (const Point& pivot : positions)
            {
                if (anchor == pivot)
                    continue;
                
                Point dxdy = anchor - pivot;

                // Include an antinode on the antenna.
                Point echo = anchor;
                while (isInBounds(echo, width, height))
                {
                    antinodes.insert(echo);
                    echo += dxdy;
                }
            }
    }


    std::cout << "Total antinodes: " << antinodes.size() << "\n";
    return 0;
}