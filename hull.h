#include "point.h"
#include <vector>
#include <algorithm>
#include <iostream>

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

/*
 * 3. Kirkpatrick
 */


void erasePoints(vector<Point>&endPoints){
    for(int i=1;i<endPoints.size()-1;i++){
        if (cross_product(endPoints[i], endPoints[i-1], endPoints[i+1])<0){
            endPoints.erase(endPoints.begin()+i);
            erasePoints(endPoints);
        }
    }
}

vector<Point> Kirkpatrick::getConvexHull(vector<Point>& points) {
    if (points.size() < 3) return points;
    vector <Point> hull;
    sort(points.begin(), points.end(), [](Point a, Point b) {
        return a.y < b.y || (a.y == b.y && a.x < b.x);
    });
    vector <Point> leftPoints;
    leftPoints.push_back(points[0]);
    for (int i = 1; i < points.size(); i++) {
        if (points[i].y != points[i - 1].y){
            leftPoints.push_back(points[i]);
        }
    }
    vector <Point> rightPoints;
    rightPoints.push_back(points[points.size()-1]);
    for (int i = points.size()-2; i >= 0; i--) {
        if (points[i].y != points[i + 1].y){
            rightPoints.push_back(points[i]);
        }
    }
    erasePoints(leftPoints);
    erasePoints(rightPoints);
    hull.insert(hull.end(), leftPoints.begin(), leftPoints.end());
    hull.insert(hull.end(), rightPoints.begin(), rightPoints.end());
    return hull;
}

/*
 * 4. Jarvis
 */


vector<Point> Jarvis::getConvexHull(vector<Point>& points) {
    if (points.size()<3) return points;
    vector<Point> hull;
}

/*
 * 5. Graham
 */

/*
 * 6. Recursive
 */

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
    Hull buildConvexHull(){
        hull = method->getConvexHull(points);
        return *this;
    }
    vector<Point> getHull(){
        return hull;
    }
};

ConvexHull *Hull::method;
void Hull::setMethod(ConvexHull *m) {
    method = m;
}