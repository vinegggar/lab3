#include <iostream>
#include <cmath>
#include "point.h"
#include <algorithm>
#include <vector>

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
            break;
        }
    }
}

vector<Point> Kirkpatrick::getConvexHull(vector<Point>& points) {
    for (auto & point : points) {
        if (point.y != (int)point.y) throw invalid_argument("y is not integer");
    }
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
    sort(points.begin(), points.end(), [](Point a, Point b) {
        return a.x < b.x || (a.x==b.x && a.y<b.y);
    });
    Point left = points[0], right = points.back();
    vector <Point> upper, lower;

    for(auto & point : points){
        if (cross_product(left, right, point) < 0) lower.push_back(point);
        else if (cross_product(left, right, point) > 0) upper.push_back(point);
    }

    upper.push_back(right);

    hull.push_back(left);
    auto on_hull = hull[0]; //upper part of hull
    for (int i=0;i<upper.size();i++){
        bool isHullEdge = true;
        for(int j=0;j<upper.size();j++){
            if (cross_product(upper[i], on_hull, upper[j]) < 0) isHullEdge = false;
        }
        if (!isHullEdge) continue;
        hull.push_back(upper[i]);
        on_hull = upper[i];
    }
    hull.push_back(right);

    lower.push_back(left);

    on_hull = hull[hull.size()-1];
    for (int i=lower.size()-1;i>=0;i--){ //analogous process for lower part of hull
        bool isHullEdge = true;
        for(int j=lower.size()-1;j>=0;j--){
            if (cross_product(lower[i], on_hull, lower[j]) < 0) isHullEdge = false;
        }
        if (!isHullEdge) continue;
        hull.push_back(lower[i]);
        on_hull = lower[i];
    }

    return hull;
}

/*
 * 5. Graham
 */


vector<Point> Graham::getConvexHull(vector<Point> &points) {
    if (points.size()<3) return points;
    vector<Point> hull;
    sort(points.begin(), points.end(), [](Point a, Point b) {
        return a.y < b.y || (a.y == b.y && a.x < b.x);
    });
    //sort the points by polar angle with respect to the lowest point
    Point lowest = points[0];
    sort(points.begin()+1, points.end(), [lowest](Point a, Point b) {
        return cross_product(lowest, a, b) > 0;
    });
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    for (int i = 2; i < points.size(); i++) {
        while (cross_product(hull[hull.size()-2], hull[hull.size()-1], points[i]) < 0){
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    return hull;
}

/*
 * 6. Recursive
 */

int findLargestTriangle(vector<Point>&points, Point a, Point b){
    int max_index = 0;
    double max_area = 0;
    for (int i=0;i<points.size();i++){
        //area of triangle = 0.5*|AB x AC|
        double area = 0.5*abs(cross_product(a, b, points[i]));
        if (area > max_area){
            max_area = area;
            max_index = i;
        }
    }
    return max_index;
}

void addToHull(vector<Point>&points, Point a, Point b, vector<Point>&hull){
    int index = findLargestTriangle(points, a, b);
    if (index == 0) return;
    hull.push_back(points[index]);
    vector<Point> left = {a}, right = {b};
    for (int i=0;i<points.size();i++){
        if (cross_product(a, points[index], points[i]) > 0) left.push_back(points[i]);
        else if (cross_product(points[index], b, points[i]) > 0) right.push_back(points[i]);
    }
    left.push_back(points[index]), right.push_back(points[index]);
    addToHull(left, a, points[index], hull);
    addToHull(right, points[index], b, hull);
}


vector<Point> Recursive::getConvexHull(vector<Point> &points) {
    if (points.size() < 3) return points;
    sort(points.begin(), points.end(), [](Point a, Point b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    Point left = points[0], right = points.back();
    vector<Point> upper={left,right}, lower={left,right};
    for (auto &point : points) {
        if (cross_product(left, right, point) < 0) lower.push_back(point);
        else if (cross_product(left, right, point) > 0) upper.push_back(point);
    }
    vector <Point> hull = {left, right};
    addToHull(upper, left, right, hull);
    addToHull(lower, right, left, hull);
    //sort by polar angle with respect to the leftmost point to get correct order
    sort(hull.begin(), hull.end(), [left](Point a, Point b) {
        return cross_product(left, a, b) > 0;
    });
    return hull;
}


class Hull {
private:
    static ConvexHull *method;
    vector<Point> points;
    vector<Point> hull;
public:
    explicit Hull(vector<Point> &p){
        points = p;
    }
    static void setMethod(ConvexHull *m);
    Hull buildConvexHull();
    vector<Point> getHull();
};

Hull Hull::buildConvexHull() {
    hull = method->getConvexHull(points);
    return *this;
}

void Hull::setMethod(ConvexHull *m) {
    method = m;
}

vector<Point> Hull::getHull() {
    return hull;
}

