#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    Point a, b;
    Edge(Point const& _a, Point const& _b) : a{_a}, b{_b} {}
    bool operator==(const Edge& other) const;
    vector <Point> getNodes();
};

struct Circle {
    double x, y, radius;
    Circle() = default;
    bool isInside(Point const& p) const;
    Point getCenter() const;
};

struct Triangle {
    Point a, b, c;
    Edge ab, bc, ac;
    Circle circle;

    Triangle(const Point& a, const Point& b, const Point& c):
            a{a}, b{b},c{c},
            ab{a, b}, bc{b, c}, ac{a, c},
            circle{} {double ax = b.x - a.x, ay = b.y - a.y, bx = c.x - a.x, by = c.y - a.y;
        double m = b.x * b.x - a.x * a.x + b.y * b.y - a.y * a.y,
                u = c.x * c.x - a.x * a.x + c.y * c.y - a.y * a.y,
                s = 1 / (2.0 * (ax * by - ay * bx));
        circle.x = ((c.y - a.y) * m + (a.y - b.y) * u) * s;
        circle.y = ((a.x - c.x) * m + (b.x - a.x) * u) * s;
        circle.radius = (a.x - circle.x) * (a.x - circle.x) + (a.y - circle.y) * (a.y - circle.y);
    }
    bool operator == (const Triangle& other) const;
    bool shareNode(const Triangle& other) const;
};

Triangle superTriangle(vector<Point>& points);

vector<Triangle> triangulate(vector<Point>& points);

vector <Triangle> delaunay(vector<Point>& points);

