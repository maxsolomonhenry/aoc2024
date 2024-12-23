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

class Grid {
private:
    int width;
    int height;
    std::map<Point, char> tiles;
public:
    Grid(int width_, int height_) : width(width_), height(height_) {}
    void add(int x, int y, char c) {
        if (!(x >+ 0 && x < width && y >= 0 && y < height))
            throw std::out_of_range("Position out of bounds");
        tiles[Point(x, y)] = c;
    }

    char read(int x, int y) {
        Point xy = Point(x, y);
        if (!tiles.count(xy) > 0)
            throw std::invalid_argument("Position not found");
        return tiles[xy];
    }
};

class Guard {
private:
    Point position;
    Direction direction;
    std::map<Point, std::vector<Direction>> path;
    Grid* grid;
public:
    Guard (Grid* grid_, Point position_, Direction direction_) : grid(grid_), position(position_), direction(direction_) {
        path[position].push_back(direction);
    }
};

int main() {
    const auto lines = util::read("src/day06/input.txt");
    std::map<Point, char> grid;
    std::map<Point, Direction> path;

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

    // Build grid from input.
    for (int x = 0; x < maxX; x++)
        for (int y = 0; y < maxY; y++)
        {
            grid[Point(x, y)] = lines[y][x];

            if (lines[y][x] == '^')
                guard = Point(x, y);
        }
    
    Direction direction = Direction::Up;

    // Calculate.
    int numBlockers = 0;
    while (guard.x >= 0 && guard.x < maxX && guard.y >= 0 && guard.y < maxY)
    {
        grid[guard] = 'X';
        path[guard] = direction;
        Point target = guard + step[direction];

        if (grid[target] == '#')
            direction = turn[direction];

        guard += step[direction];
    }

    int numX = 0;
    for (int x = 0; x < maxX; x++)
    {
        for (int y = 0; y < maxY; y++)
        {
            if (grid[Point(x, y)] == 'X')
            {
                numX++;
                numBlockers += isBlocker(grid, path, Point(x, y), maxX, maxY);
            }
            std::cout << grid[Point(x, y)];
        }
        std::cout << "\n";
    }


    std::cout << "Num visited squares: " << numX << '\n';
    std::cout << "Num blockers: " << numBlockers << '\n';

    return 0;
}