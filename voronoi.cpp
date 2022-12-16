#include <vector>
#include "point.h"
#include "delaunay.h"

using namespace std;

bool areNeighbours(Triangle const& t1, Triangle const& t2) {
    return t1.ab == t2.ab || t1.ab == t2.bc || t1.ab == t2.ac ||
           t1.bc == t2.ab || t1.bc == t2.bc || t1.bc == t2.ac ||
           t1.ac == t2.ab || t1.ac == t2.bc || t1.ac == t2.ac;
}

vector<Edge> voronoi(vector<Point>&points){
    vector<Edge> voronoi;
    vector<Triangle> triangles = triangulate(points);
    for (int i = 0; i < triangles.size(); i++) {
        for (int j = i + 1; j < triangles.size(); j++) {
            if (areNeighbours(triangles[i], triangles[j])) {
                voronoi.emplace_back(triangles[i].circle.getCenter(), triangles[j].circle.getCenter());
            }
        }
    }
    return voronoi;
}