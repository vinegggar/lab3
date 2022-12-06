#include <iostream>
using namespace std;

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
    Point() : x(0), y(0) {}
    void printPoint() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
    bool operator == (const Point& p) const {
        return x == p.x && y == p.y;
    }
};

double cross_product(Point A, Point B, Point C) {
    //cross product of vectors AB and AC
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}
