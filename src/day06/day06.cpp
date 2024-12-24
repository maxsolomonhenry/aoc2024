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

    std::map<Direction, Point> dxdy = {
        {Direction::Up, Point(0, -1)},
        {Direction::Down, Point(0, 1)},
        {Direction::Left, Point(-1, 0)},
        {Direction::Right, Point{1, 0}},
    };

    std::map<Direction, Direction> turnLookup {
        {Direction::Up, Direction::Right},
        {Direction::Down, Direction::Left},
        {Direction::Left, Direction::Up},
        {Direction::Right, Direction::Down},        
    };

public:
    Guard (Point position_, Direction direction_) : position(position_), direction(direction_) {
        log();
    }

    // Copy constructor.
    Guard(const Guard& other) : 
        position(other.position),
        direction(other.direction),
        path(other.path),
        dxdy(other.dxdy),
        turnLookup(other.turnLookup) {}

    Point getPosition() {
        return position;
    }

    void log() {
        path[position].push_back(direction);
    }

    void turn() {
        direction = turnLookup[direction];
    }

    void step() {
        position += dxdy[direction];
        log();
    }

    Point getTarget() {
        return position + dxdy[direction];
    }

    std::map<Point, std::vector<Direction>> getPath() {
        return path;
    }

    bool isDejaVu(Point target) {
        if (path.count(target) == 0)
            return false;

        return (std::count(path[target].begin(), path[target].end(), direction) > 0);
    }

    void place(Point position_, Direction direction_) {
        position = position_;
        direction = direction_;
    }
};

bool isLoop(Grid grid, Guard sentry) {
    while (true) {
        if (!grid.isInBounds(sentry.getTarget()))
            return false;

        while (grid.read(sentry.getTarget()) == '#') {
            sentry.turn();
            if (sentry.isDejaVu(sentry.getTarget()))
                return true;
        }

        if (sentry.isDejaVu(sentry.getTarget()))
            return true;

        sentry.step();
    }
}

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
    
    Guard guard(start, Direction::Up);

    while (true) {

        if (!grid.isInBounds(guard.getTarget()))
            break;

        while (grid.read(guard.getTarget()) == '#')
            guard.turn();

        guard.step();
    }

    std::cout << "Num visited squares: " << guard.getPath().size() << '\n';

    int nLoops = 0;
    for (const auto& [position, directions] : guard.getPath()) {
        
        // Make a copy of original path, but start at this point.
        for (const auto& direction : directions) {
            Guard sentry = guard;
            sentry.place(position, direction);
            sentry.turn();

            nLoops += isLoop(grid, sentry);
            std::cout << "Num loops: " << nLoops << '\n';
        }
    }

    std::cout << "Done!\n";

    return 0;
}