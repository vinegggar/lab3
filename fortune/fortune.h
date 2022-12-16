#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Parabola {
    Point focus;
    double directrix;
    Parabola(Point focus, double directrix) : focus(focus), directrix(directrix) {}
    Point findIntersection(Parabola other) const;
};

struct Arc {
    Parabola parabola;
    Point *rightFocus;
    Arc(Parabola parabola, Point *rightFocus) : parabola(parabola), rightFocus(rightFocus) {}
    bool operator < (const Arc& other) const;
};

class FortuneEvent {
public:
    Point point;
    bool isSiteEvent;
    FortuneEvent(Point point, bool isSiteEvent) : point(point), isSiteEvent(isSiteEvent) {}
    bool operator < (const FortuneEvent& other) const;
};

typedef pair<Point, Point> Edge;

const int WIDTH = 800;
const int HEIGHT = 600;


void handleSiteEvent(Point site, set <Arc>& beachline, vector <FortuneEvent>& eventQueue, vector <Edge>& edges);

void handleCircleEvent(Point site, set <Arc>& beachline, vector <FortuneEvent>& eventQueue, vector <Edge>& edges);

vector <Edge> Voronoi(vector <Point>& points);