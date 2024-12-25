struct Point {
    int x, y;

    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    Point operator+(const Point &addend) const {
        return Point(x + addend.x, y + addend.y);
    }

    Point operator-(const Point &addend) const {
        return Point(x - addend.x, y - addend.y);
    }

    Point& operator+=(const Point &addend) {
        x += addend.x;
        y += addend.y;
        return *this;
    }

    Point& operator-=(const Point &addend) {
        x -= addend.x;
        y -= addend.y;
        return *this;
    }

    bool operator<(const Point &comparand) const {
        if (x != comparand.x) return x < comparand.x;
        return y < comparand.y;
    }

    bool operator==(const Point &comparand) const {
        return (x == comparand.x) && (y == comparand.y);
    }
};


namespace std {
    template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };
}