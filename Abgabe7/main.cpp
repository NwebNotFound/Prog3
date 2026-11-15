#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

struct Point {
    int x;
    int y;
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual void print(std::ostream& os) const = 0;
};

class Circle : public Shape {
public:
    Circle(Point center, int radius) : center_(center), radius_(radius) {}

    void print(std::ostream& os) const override {
        os << "Circle (" << center_.x << "," << center_.y << "), r=" << radius_ << '\n';
    }

private:
    Point center_;
    int radius_;
};

class Line : public Shape {
public:
    Line(Point from, Point to) : from_(from), to_(to) {}

    void print(std::ostream& os) const override {
        os << "Line (" << from_.x << "," << from_.y << ")->(" << to_.x << "," << to_.y << ")\n";
    }

private:
    Point from_;
    Point to_;
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(Point{1, 2}, 3));
    shapes.push_back(std::make_unique<Circle>(Point{-1, 0}, 4));
    shapes.push_back(std::make_unique<Line>(Point{-10, -10}, Point{10, 10}));

    for (auto& x : shapes) {
        x->print(std::cout);
    }
}
