#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

class Point3D{
public:
    double x;
    double y;
    double z;

    //Point3D() : x(0), y(0), z(0) {}
    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

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

class StarOne {
public:
    Point3D a;
    Point3D b;
    Point3D c;
    Point3D d;
    Point3D e;

    Point3D o;
    Point3D p;
    Point3D q;
    Point3D r;
    Point3D s;

    StarOne(int cx, int cy, int radius) {
        double angle = 72.0;
        a = Point3D(cx + radius*cos(angle * 1 * M_PI / 180), cy + radius*sin(angle * 1 * M_PI / 180), 0);
        b = Point3D(cx + radius*cos(angle * 2 * M_PI / 180), cy + radius*sin(angle * 2 * M_PI / 180), 0);
        c = Point3D(cx + radius*cos(angle * 3 * M_PI / 180), cy + radius*sin(angle * 3 * M_PI / 180), 0);
        d = Point3D(cx + radius*cos(angle * 4 * M_PI / 180), cy + radius*sin(angle * 4 * M_PI / 180), 0);
        e = Point3D(cx + radius*cos(angle * 5 * M_PI / 180), cy + radius*sin(angle * 5 * M_PI / 180), 0);

        o = Point3D(cx + radius*cos(angle * 1 * M_PI / 180), cy + radius*sin(angle * 1 * M_PI / 180), radius/2);
        p = Point3D(cx + radius*cos(angle * 2 * M_PI / 180), cy + radius*sin(angle * 2 * M_PI / 180), radius/2);
        q = Point3D(cx + radius*cos(angle * 3 * M_PI / 180), cy + radius*sin(angle * 3 * M_PI / 180), radius/2);
        r = Point3D(cx + radius*cos(angle * 4 * M_PI / 180), cy + radius*sin(angle * 4 * M_PI / 180), radius/2);
        s = Point3D(cx + radius*cos(angle * 5 * M_PI / 180), cy + radius*sin(angle * 5 * M_PI / 180), radius/2);
    }

    void draw() {
        setcolor(5);
        line(a.x, a.y, c.x, c.y);
        line(b.x, b.y, d.x, d.y);
        line(c.x, c.y, e.x, e.y);
        line(d.x, d.y, a.x, a.y);
        line(e.x, e.y, b.x, b.y);

        line(o.x, o.y, q.x, q.y);
        line(p.x, p.y, r.x, r.y);
        line(q.x, q.y, s.x, s.y);
        line(r.x, r.y, o.x, o.y);
        line(s.x, s.y, p.x, p.y);

        line(o.x, o.y, a.x, a.y);
        line(p.x, p.y, b.x, b.y);
        line(q.x, q.y, c.x, c.y);
        line(r.x, r.y, d.x, d.y);
        line(s.x, s.y, e.x, e.y);

        setfillstyle(SOLID_FILL, 10);
        fillellipse(a.x, a.y, 4, 4);
        fillellipse(b.x, b.y, 4, 4);
        fillellipse(c.x, c.y, 4, 4);
        fillellipse(d.x, d.y, 4, 4);
        fillellipse(e.x, e.y, 4, 4);

        fillellipse(o.x, o.y, 4, 4);
        fillellipse(p.x, p.y, 4, 4);
        fillellipse(q.x, q.y, 4, 4);
        fillellipse(r.x, r.y, 4, 4);
        fillellipse(s.x, s.y, 4, 4);
    }

    void rotateY(int cx, int cy, int cz, int angle) {
        a.rotateY(cx, cy, cz, angle);
        b.rotateY(cx, cy, cz, angle);
        c.rotateY(cx, cy, cz, angle);
        d.rotateY(cx, cy, cz, angle);
        e.rotateY(cx, cy, cz, angle);

        o.rotateY(cx, cy, cz, angle);
        p.rotateY(cx, cy, cz, angle);
        q.rotateY(cx, cy, cz, angle);
        r.rotateY(cx, cy, cz, angle);
        s.rotateY(cx, cy, cz, angle);
    }

    void rotateX(int cx, int cy, int cz, int angle) {
        a.rotateX(cx, cy, cz, angle);
        b.rotateX(cx, cy, cz, angle);
        c.rotateX(cx, cy, cz, angle);
        d.rotateX(cx, cy, cz, angle);
        e.rotateX(cx, cy, cz, angle);

        o.rotateX(cx, cy, cz, angle);
        p.rotateX(cx, cy, cz, angle);
        q.rotateX(cx, cy, cz, angle);
        r.rotateX(cx, cy, cz, angle);
        s.rotateX(cx, cy, cz, angle);
    }

    void rotateZ(int cx, int cy, int cz, int angle) {
        a.rotateZ(cx, cy, cz, angle);
        b.rotateZ(cx, cy, cz, angle);
        c.rotateZ(cx, cy, cz, angle);
        d.rotateZ(cx, cy, cz, angle);
        e.rotateZ(cx, cy, cz, angle);

        o.rotateZ(cx, cy, cz, angle);
        p.rotateZ(cx, cy, cz, angle);
        q.rotateZ(cx, cy, cz, angle);
        r.rotateZ(cx, cy, cz, angle);
        s.rotateZ(cx, cy, cz, angle);
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    StarOne uno(centerX, centerY, 200);

    bool pivot = false;

    while (true) {
        cleardevice();
        outtextxy(getmaxx() - 120, getmaxy() - 130, "Star...");
        outtextxy(getmaxx() - 120, getmaxy() - 110, "Rotation : A or B");
        outtextxy(getmaxx() - 120, getmaxy() - 90, "Rotation : W or S");
        outtextxy(getmaxx() - 120, getmaxy() - 70, "Rotation : Q or E");
        outtextxy(getmaxx() - 120, getmaxy() - 50, "Pause : X");
        outtextxy(getmaxx() - 120, getmaxy() - 30, "Continue : Z");

        if (kbhit()) {
            char key = getch();
            if (key == 'a' || key == 'A') {
                uno.rotateY(centerX, centerY, 0, -1);
            } else if (key == 'd' || key == 'd') {
                uno.rotateY(centerX, centerY, 0, 1);
            }else if (key == 'w' || key == 'W') {
                uno.rotateX(centerX, centerY, 0, 1);
            }else if (key == 's' || key == 'S') {
                uno.rotateX(centerX, centerY, 0, -1);
            }else if (key == 'q' || key == 'Q') {
                uno.rotateZ(centerX, centerY, 0, 1);
            }else if (key == 'e' || key == 'E') {
                uno.rotateZ(centerX, centerY, 0, -1);
            }else if (key == 'z' || key == 'Z') {
                pivot = true;
            }else if (key == 'x' || key == 'X') {
                pivot = false;
            } else {
                closegraph();
            }
        }

        uno.draw();
        if(pivot)
            uno.rotateY(centerX, centerY, 0, 1);
        delay(16);
    }
    getch();
    closegraph();
    return 0;
}
