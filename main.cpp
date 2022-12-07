#include <SFML/Graphics.hpp>
#include "hull.h"
#include <cmath>
using namespace sf;
using namespace std;

void drawLine(RenderWindow &window, Point p1, Point p2, Color color=Color::Blue, int thickness = 1) {
    if (thickness>1) {
        RectangleShape line(Vector2f(sqrt(pow(p2.x - p1.x, 2) +pow(p2.y - p1.y, 2)), thickness));
        line.setPosition(p1.x, p1.y);
        line.setFillColor(color);
        double angle = atan2(p2.y - p1.y, p2.x - p1.x) * 180 / M_PI;
        line.rotate(angle);
        window.draw(line);
    }
    else {
        Vertex line[] = {
            Vertex(Vector2f(p1.x, p1.y)),
            Vertex(Vector2f(p2.x, p2.y))
        };
        line->color = color;
        window.draw(line, 2, Lines);
    }
}

void drawPoint(RenderWindow &window, Point p) {
    CircleShape circle(3);
    circle.setFillColor(Color::Red);
    circle.setPosition(p.x, p.y);
    window.draw(circle);
}

void drawPolygon(RenderWindow &window, vector<Point> points, Color color=Color::Blue, int thickness = 1) {
    for (int i = 0; i < points.size() - 1 ; i++) {
        drawLine(window, points[i], points[i + 1], color, thickness);
    }
    drawLine(window, points[0], points[points.size() - 1], color, thickness);
}

void drawHull(RenderWindow &window, vector<Point> points, Color color=Color::Blue, int thickness = 1) {
    Hull hull(points);
    Hull convex = hull.buildConvexHull();
    drawPolygon(window, convex.getHull(), color, thickness);
}

vector<Point> generatePoints(int n) {
    vector<Point> points;
    for (int i = 0; i < n; i++) {
        points.push_back(Point(rand() % 600 + 100, rand() % 400 + 100));
    }
    return points;
}

int main()
{
    srand(time(nullptr));
    vector <Point> test = generatePoints(42);

    RenderWindow window(VideoMode(800, 600), "Convex Hull");
    window.setView(View(FloatRect(0, 600, 800, -600)));
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        for (int i = 0; i < 800; i += 50) {
            drawLine(window, Point(i, 0), Point(i, 600), Color(220, 220, 220),1);
        }
        for (int i = 0; i < 600; i += 50) {
            drawLine(window, Point(0, i), Point(800, i), Color(220, 220, 220),1);
        }

        for (Point p: test) {
            drawPoint(window, p);
        }
        Hull::setMethod(new Graham);
        drawHull(window, test, Color::Blue, 2);
        window.display();
    }
    return 0;
}