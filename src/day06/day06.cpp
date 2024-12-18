#include "../common/util.h"

#include <iostream>
#include <map>

struct Point {
    int x, y;

    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    Point operator+(const Point &addend) const {
        return Point(x + addend.x, y + addend.y);
    }

    Point& operator+=(const Point &addend) {
        x += addend.x;
        y += addend.y;
        return *this;
    }

    bool operator<(const Point &comparand) const {
        if (x != comparand.x) return x < comparand.x;
        return y < comparand.y;
    }
    
};

enum class Direction {
    Up,
    Left,
    Down,
    Right
};



int main() {
    const auto lines = util::read("src/day06/input.txt");
    std::map<Point, char> grid;

    std::map<Direction, Point> step = {
        {Direction::Up, Point(0, -1)},
        {Direction::Down, Point(0, 1)},
        {Direction::Left, Point(-1, 0)},
        {Direction::Right, Point{1, 0}},
    };

    std::map<Direction, Direction> turn {
        {Direction::Up, Direction::Right},
        {Direction::Down, Direction::Left},
        {Direction::Left, Direction::Up},
        {Direction::Right, Direction::Down},        
    };

    int maxX = lines[0].size();
    int maxY = lines.size();

    Point guard(-1, -1);

    for (int x = 0; x < maxX; x++)
        for (int y = 0; y < maxY; y++)
        {
            grid[Point(x, y)] = lines[y][x];

            if (lines[y][x] == '^')
                guard = Point(x, y);
        }
    
    Direction direction = Direction::Up;

    while (guard.x >= 0 && guard.x < maxX && guard.y >= 0 && guard.y < maxY)
    {
        grid[guard] = 'X';
        Point target = guard + step[direction];

        if (grid[target] == '#')
            direction = turn[direction];

        guard += step[direction];
    }

    int numX = 0;
    for (int x = 0; x < maxX; x++)
        for (int y = 0; y < maxY; y++)
            if (grid[Point(x, y)] == 'X') numX++;

    std::cout << "Num visited squares: " << numX << '\n';

    return 0;
}