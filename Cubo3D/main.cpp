#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

class Point3D{
public:
    double x;
    double y;
    double z;

    Point3D() : x(0), y(0), z(0) {}
    explicit Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    void rotateX(int cx, int cy, int cz, double angle) {
        double temp = ((y - cy)*cos(angle * M_PI / 180) - (z - cz)*sin(angle * M_PI / 180)) + cy;
        z = ((y - cy)*sin(angle * M_PI / 180) + (z - cz)*cos(angle * M_PI / 180)) + cz;
        y = temp;
    }

    void rotateY(int cx, int cy, int cz, double angle) {
        double temp = ((x - cx)*cos(angle * M_PI / 180) + (z - cz)*sin(angle * M_PI / 180)) + cx;
        z = (-(x - cx)*sin(angle * M_PI / 180) + (z - cz)*cos(angle * M_PI / 180)) + cz;
        x = temp;
    }

    void rotateZ(int cx, int cy, int cz, double angle) {
        double temp = ((x - cx)*cos(angle * M_PI / 180) - (y - cy)*sin(angle * M_PI / 180)) + cx;
        y = ((x - cx)*sin(angle * M_PI / 180) + (y - cy)*cos(angle * M_PI / 180)) + cy;
        x = temp;
    }
};


int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    Point3D a(100, 100, 0);
    Point3D b(200, 100, 0);
    Point3D c(100, 200, 0);
    Point3D d(200, 200, 0);

    Point3D o(110, 110, 100);
    Point3D p(210, 110, 100);
    Point3D q(110, 210, 100);
    Point3D r(210, 210, 100);

    while (!kbhit()) {
        cleardevice();
        line(a.x, a.y, b.x, b.y);
        line(b.x, b.y, d.x, d.y);
        line(c.x, c.y, d.x, d.y);
        line(a.x, a.y, c.x, c.y);

        line(o.x, o.y, p.x, p.y);
        line(p.x, p.y, r.x, r.y);
        line(q.x, q.y, r.x, r.y);
        line(o.x, o.y, q.x, q.y);

        line(a.x, a.y, o.x, o.y);
        line(b.x, b.y, p.x, p.y);
        line(c.x, c.y, q.x, q.y);
        line(d.x, d.y, r.x, r.y);

        a.rotateY(150, 150, 0, 5);
        b.rotateY(150, 150, 0, 5);
        c.rotateY(150, 150, 0, 5);
        d.rotateY(150, 150, 0, 5);

        o.rotateY(150, 150, 0, 5);
        p.rotateY(150, 150, 0, 5);
        q.rotateY(150, 150, 0, 5);
        r.rotateY(150, 150, 0, 5);

        delay(60);

        line(a.x, a.y, b.x, b.y);
        line(b.x, b.y, d.x, d.y);
        line(c.x, c.y, d.x, d.y);
        line(a.x, a.y, c.x, c.y);

        line(o.x, o.y, p.x, p.y);
        line(p.x, p.y, r.x, r.y);
        line(q.x, q.y, r.x, r.y);
        line(o.x, o.y, q.x, q.y);

        line(a.x, a.y, o.x, o.y);
        line(b.x, b.y, p.x, p.y);
        line(c.x, c.y, q.x, q.y);
        line(d.x, d.y, r.x, r.y);

    }
    getch();
    closegraph();
    return 0;
}
