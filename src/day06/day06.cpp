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
    void add(Point point, char c) {
        if (!isInBounds(point))
            throw std::out_of_range("Position out of bounds");
        tiles[point] = c;
    }

    char read(Point xy) {
        if (!(tiles.count(xy) > 0))
            throw std::invalid_argument("Position not found");
        return tiles[xy];
    }

    bool isInBounds(Point point) {
        return (point.x >= 0 && point.x < width && point.y >= 0 && point.y < height);
    }
};

class Guard {
private:
    Point position;
    Direction direction;
    std::map<Point, std::vector<Direction>> path;
    Grid* grid;

    std::map<Direction, Point> dxdy = {
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

public:
    Guard (Grid* grid_, Point position_, Direction direction_) : grid(grid_), position(position_), direction(direction_) {
        log();
    }

    Point getPosition() {
        return position;
    }

    void log() {
        path[position].push_back(direction);
    }

    bool step() {
        Point target = position + dxdy[direction];

        if (!grid->isInBounds(target))
            return false;

        if (grid->read(target) == '#')
            direction = turn[direction];

        position += dxdy[direction];

        log();

        return true;
    }

    int getNumVisitedTiles() {
        return path.size();
    }
};

int main() {
    const auto lines = util::read("src/day06/input.txt");

    int width = lines[0].size();
    int height = lines.size();
    Grid grid(width, height);
    Point start;

    // Build grid from input.
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        {
            grid.add(Point(x, y), lines[y][x]);

            if (lines[y][x] == '^')
                start = Point(x, y);
        }
    
    Guard guard(&grid, start, Direction::Up);

    while (guard.step()) {};

    std::cout << "Num visited squares: " << guard.getNumVisitedTiles() << '\n';

    return 0;
}