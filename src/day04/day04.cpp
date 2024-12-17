#include "../common/util.h"

#include <iostream>
#include <map>

enum class Direction {
    UPLEFT,
    UP, 
    UPRIGHT,
    LEFT,
    RIGHT,
    DOWNLEFT,
    DOWN,
    DOWNRIGHT
};


std::pair<int, int> getIncrement(const Direction &direction)
{
    int dx;
    int dy;

    switch(direction) {
        case Direction::UPLEFT:
            dx = -1;
            dy = -1;
            break;
        case Direction::UP:
            dx = 0;
            dy = -1;
            break;
        case Direction::UPRIGHT:
            dx = 1;
            dy = -1;
            break;
        case Direction::LEFT:
            dx = -1;
            dy = 0;
            break;
        case Direction::RIGHT:
            dx = 1;
            dy = 0;
            break;
        case Direction::DOWNLEFT:
            dx = -1;
            dy = 1;
            break;
        case Direction::DOWN:
            dx = 0;
            dy = 1;
            break;
        case Direction::DOWNRIGHT:
            dx = 1;
            dy = 1;
            break;
    }

    return std::pair<int, int>(dx, dy);
}


bool hasXmas(const std::vector<std::string> &lines, const size_t &x, const size_t &y, const Direction &direction) {

    static const std::string kPattern = "XMAS";

    // Um, re-determine boundaries (this should really be a class, eh).
    static const size_t &maxX = lines[0].size();
    static const size_t &maxY = lines.size();

    int xx = static_cast<int>(x);
    int yy = static_cast<int>(y);

    std::pair<int, int> incr = getIncrement(direction);
    const int &dx = incr.first;
    const int &dy = incr.second;

    // Start on 1 because first letter has been confirmed.
    for (int i = 1; i < 4; i++)
    {
        xx += dx;
        yy += dy;

        if (xx < 0 || xx > maxX || yy < 0 || yy > maxY)
            return false;

        if (lines[yy][xx] != kPattern[i])
            return false;
    }

    return true;
}


int findNumXmas(const std::vector<std::string> &lines, const size_t &x, const size_t &y) {

    if (lines[y][x] != 'X')
        return 0;

    // Determine boundaries.
    static const size_t &maxX = lines[0].size();
    static const size_t &maxY = lines.size();

    static const std::map<std::pair<size_t, size_t>, Direction> lookup = {
        {{0, 0}, Direction::UPLEFT},
        {{1, 0}, Direction::UP},
        {{2, 0}, Direction::UPRIGHT},
        {{0, 1}, Direction::LEFT},
        {{2, 1}, Direction::RIGHT},
        {{0, 2}, Direction::DOWNLEFT},
        {{1, 2}, Direction::DOWN},
        {{2, 2}, Direction::DOWNRIGHT}
    };

    std::vector<Direction> directions;

    // Determine direction.
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
        {
            size_t xx = x + i - 1;
            size_t yy = y + j - 1;

            // Only need to check maxima, as `size_t` will wrap to large values 
            // if negative.
            if (xx >= maxX || yy >= maxY)
                continue;

            if (lines[yy][xx] == 'M')
                directions.push_back(lookup.at({i, j}));
        }

    int nXmas = 0;
    for (auto direction : directions)
        if (hasXmas(lines, x, y, direction)) nXmas++;

    return nXmas;
}


bool hasMas(const std::vector<std::string> &lines, size_t x, size_t y, Direction direction) {
    static const size_t &maxX = lines[0].size();
    static const size_t &maxY = lines.size();

    if (x < 1 || x >= (maxX - 1) || y < 1 || y >= (maxY - 1))
        return false;

    size_t dy = (direction == Direction::UPLEFT) ? -1 : 1;

    if (lines[y + dy][x - 1] == 'M' && lines[y - dy][x + 1] == 'S' || lines[y + dy][x - 1] == 'S' && lines[y - dy][x + 1] == 'M')
        return true;

    return false;
}

int findNumMas(const std::vector<std::string> &lines, size_t x, size_t y) {
    if (lines[y][x] != 'A')
        return 0;

    if(hasMas(lines, x, y, Direction::UPLEFT) && hasMas(lines, x, y, Direction::DOWNLEFT))
        return 1;
    
    return 0;
}


int main() {
    auto lines = util::read("src/day04/input.txt");
    int nXmas = 0;
    int nMas = 0;

    for (size_t y = 0; y < lines.size(); y++)
        for (size_t x = 0; x < lines[y].size(); x++)
        {
            nXmas += findNumXmas(lines, x, y);
            nMas += findNumMas(lines, x, y);
        }

    std::cout << "Number of XMAS: " << nXmas << '\n';
    std::cout << "Number of MAS: " << nMas << '\n';

    return 0;
}
