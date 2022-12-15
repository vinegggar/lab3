#include <iostream>
using namespace std;

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
    Point() : x(0), y(0) {}
    void printPoint() const;
    bool operator == (const Point& p) const;
    bool operator !=(const Point& p) const;
};

double cross_product(Point A, Point B, Point C) ;

