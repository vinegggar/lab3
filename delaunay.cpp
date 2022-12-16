#include <algorithm>
#include <iostream>
#include <vector>
#include "point.h"

using namespace std;

struct Edge {
    Point a, b;
    Edge(Point const& _a, Point const& _b) : a{_a}, b{_b} {}
    bool operator==(const Edge& other) const;
    vector <Point> getNodes();
};

bool Edge::operator==(const Edge& other) const {
    return (a == other.a && b == other.b) || (a == other.b && b == other.a);
}

vector <Point> Edge::getNodes() {
    return {a, b};
}

struct Circle {
    double x, y, radius;
    Circle() = default;
    bool isInside(Point const& p) const;
    Point getCenter() const;
};

Point Circle::getCenter() const {
    return {x, y};
}

bool Circle::isInside(Point const& p) const {
    return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y) <= radius;
}

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

bool Triangle::operator==(const Triangle& other) const {
    return (a == other.a && b == other.b && c == other.c) ||
           (a == other.a && b == other.c && c == other.b) ||
           (a == other.b && b == other.a && c == other.c) ||
           (a == other.b && b == other.c && c == other.a) ||
           (a == other.c && b == other.a && c == other.b) ||
           (a == other.c && b == other.b && c == other.a);
}

bool Triangle::shareNode(const Triangle& other) const {
    return a == other.a || a == other.b || a == other.c ||
           b == other.a || b == other.b || b == other.c ||
           c == other.a || c == other.b || c == other.c;
}

Triangle superTriangle(vector<Point>& points) {
    vector <Point> p = points;
    sort(p.begin(), p.end(), [](Point a, Point b) {return a.x < b.x;});
    double min_x = p[0].x, max_x = p[p.size() - 1].x;
    sort(p.begin(), p.end(), [](Point a, Point b) {return a.y < b.y;});
    double min_y = p[0].y, max_y = p[p.size() - 1].y;
    double dx = max_x - min_x, dy = max_y - min_y,
            d_max = max(dx, dy),
            x_mid = (min_x + max_x) / 2.0,
            y_mid = (min_y + max_y) / 2.0;
    return {Point(x_mid - 100 * d_max, y_mid - d_max),
            Point(x_mid, y_mid + 100 * d_max),
            Point(x_mid + 100 * d_max, y_mid - d_max)};
}

vector<Triangle> triangulate(vector<Point>& points){
    if (points.size() < 3) throw invalid_argument("Need at least 3 points");
    Triangle super = superTriangle(points);
    vector <Triangle> d = {super};
    for (Point& point : points) {
        vector<Triangle> badTriangles;
        for (Triangle &triangle: d) {
            if (triangle.circle.isInside(point))
                badTriangles.push_back(triangle);
        }
        vector<Edge> polygon;
        for (Triangle &triangle: badTriangles) {
            for (const Edge& edge: {triangle.ab, triangle.bc, triangle.ac}) {
                int count = 0;
                for (Triangle &t: badTriangles) {
                    if (t.ab == edge || t.bc == edge || t.ac == edge)
                        count++;
                }
                if (count == 1) polygon.push_back(edge);
            }
        }
        for (Edge &edge: polygon) d.emplace_back(Triangle{edge.a, edge.b, point});
        d.erase(remove_if(d.begin(), d.end(), [&badTriangles](Triangle const& t) {
            return find(badTriangles.begin(), badTriangles.end(), t) != badTriangles.end();
        }), d.end());
    }
    return d;
}

vector <Triangle> delaunay(vector<Point>& points) {
    vector <Triangle> triangles = triangulate(points);
    vector <Triangle> result;
    for (Triangle& triangle: triangles) {
        if (!triangle.shareNode(superTriangle(points))) result.push_back(triangle);
    }
    return result;
}