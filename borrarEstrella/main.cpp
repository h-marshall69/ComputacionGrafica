#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159265;

class Point2D {
public:
    int x;
    int y;

    Point2D() : x(0), y(0) {}
    Point2D(int x, int y) : x(x), y(y) {}
};

void printPoint(const Point2D& point) {
    cout << "(" << point.x << ", " << point.y << ")" << endl;
}

void drawPentagram(int cx, int cy, int radius) {
    const int numVertices = 5;
    Point2D vertices[numVertices];

    // Calcula las coordenadas de los vértices del pentágono regular
    double angle = 360.0 / numVertices;
    cout << angle << endl;
    for (int i = 0; i < numVertices; ++i) {
        double theta = (angle * i) * (PI / 180.0);
        vertices[i].x = cx + radius * cos(theta);
        vertices[i].y = cy + radius * sin(theta);
    }

    // Dibuja el pentagrama
    for (int i = 0; i < numVertices; ++i) {
        printPoint(vertices[i]);
        line(vertices[i].x, vertices[i].y, vertices[(i + 2) % numVertices].x, vertices[(i + 2) % numVertices].y);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int cx = 120; // Coordenada x del centro del pentagrama
    int cy = 200; // Coordenada y del centro del pentagrama
    int radius = 100; // Radio del pentagrama

    drawPentagram(cx, cy, radius);

    getch();
    closegraph();
    return 0;
}
