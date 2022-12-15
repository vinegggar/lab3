#include <vector>
#include <set>
#include <algorithm>
#include "../point.h"

using namespace std;

struct Parabola {
    Point focus;
    double directrix;
    Parabola(Point focus, double directrix) : focus(focus), directrix(directrix) {}
    Point findIntersection(Parabola other) const {
        double x = (other.focus.x * other.focus.x - focus.x * focus.x + focus.y * focus.y - other.focus.y * other.focus.y) / (2 * (other.focus.y - focus.y));
        double y = focus.y + (x - focus.x) * (x - focus.x) / (2 * (focus.y - directrix));
        return {x, y};
    }
};

struct Arc {
    //arc represented by parabola and pointer to next arc's focus
    Parabola parabola;
    Point *rightFocus;
    Arc(Parabola parabola, Point *rightFocus) : parabola(parabola), rightFocus(rightFocus) {}
    //compare arcs by their x coordinate at the given y
    bool operator < (const Arc& other) const {
        return parabola.findIntersection(other.parabola).x < min(rightFocus->x, other.rightFocus->x);
    }
};

class FortuneEvent {
public:
    Point point;
    bool isSiteEvent;
    FortuneEvent(Point point, bool isSiteEvent) : point(point), isSiteEvent(isSiteEvent) {}
    bool operator < (const FortuneEvent& other) const {
        return point.y < other.point.y || (point.y == other.point.y && point.x < other.point.x);
    }
};

typedef pair<Point, Point> Edge;

const int WIDTH = 800;
const int HEIGHT = 600;


void handleSiteEvent(Point site, set <Arc>& beachline, vector <FortuneEvent>& eventQueue, vector <Edge>& edges) {
}


void handleCircleEvent(Point site, set <Arc>& beachline, vector <FortuneEvent>& eventQueue, vector <Edge>& edges) {
}

vector <Edge> Voronoi(vector <Point>& points) {
    vector <Edge> edges;
    vector <FortuneEvent> eventQueue;
    set <Arc> beachline;
    for (Point p : points) {
        eventQueue.push_back(FortuneEvent(p, true));
    }
    sort(eventQueue.begin(), eventQueue.end());
    while (!eventQueue.empty()) {
        FortuneEvent event = eventQueue.back();
        eventQueue.pop_back();
        if (event.isSiteEvent) {
            handleSiteEvent(event.point, beachline, eventQueue, edges);
        }
        else {
            handleCircleEvent(event.point, beachline, eventQueue, edges);
        }
    }
    return edges;
}