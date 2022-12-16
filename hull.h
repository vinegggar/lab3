#include "point.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

class ConvexHull {
public:
    virtual vector<Point> getConvexHull(vector<Point>& points) = 0;
};

class Kirkpatrick: public ConvexHull {
    vector<Point> getConvexHull(vector<Point>& points) override;
};

class Jarvis : public ConvexHull {
    vector<Point> getConvexHull(vector<Point>& points) override;
};

class Graham : public ConvexHull {
    vector<Point> getConvexHull(vector<Point>& points) override;
};

class Recursive : public ConvexHull {
    vector<Point> getConvexHull(vector<Point>& points) override;
};

void erasePoints(vector<Point>&endPoints);

int findLargestTriangle(vector<Point>&points, Point a, Point b);

void addToHull(vector<Point>&points, Point a, Point b, vector<Point>&hull);


class Hull {
private:
    static ConvexHull *method;
    vector<Point> points;
    vector<Point> hull;
public:
    Hull(vector<Point> &p){
        points = p;
    }
    static void setMethod(ConvexHull *m);
    Hull buildConvexHull();
    vector<Point> getHull();
};

ConvexHull *Hull::method;