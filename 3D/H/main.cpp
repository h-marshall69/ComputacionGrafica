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

class Hache{
    public:
    Point3D a[12];
    Point3D b[12];
    int n = 12;

    Hache(int cx, int cy, int radius) {
        double angle = 72.0;
        a[0] = Point3D(cx - radius, cy - radius, 0);
        a[1] = Point3D(cx - radius/3, cy - radius, 0);
        a[2] = Point3D(cx - radius/3, cy - radius/3, 0);
        a[3] = Point3D(cx + radius/3, cy - radius/3, 0);
        a[4] = Point3D(cx + radius/3, cy - radius, 0);
        a[5] = Point3D(cx + radius, cy - radius, 0);
        a[6] = Point3D(cx + radius, cy + radius, 0);
        a[7] = Point3D(cx + radius/3, cy + radius, 0);
        a[8] = Point3D(cx + radius/3, cy + radius/3, 0);
        a[9] = Point3D(cx - radius/3, cy + radius/3, 0);
        a[10] = Point3D(cx - radius/3, cy + radius, 0);
        a[11] = Point3D(cx - radius, cy + radius, 0);

        b[0] = Point3D(cx - radius, cy - radius, radius/2);
        b[1] = Point3D(cx - radius/3, cy - radius, radius/2);
        b[2] = Point3D(cx - radius/3, cy - radius/3, radius/2);
        b[3] = Point3D(cx + radius/3, cy - radius/3, radius/2);
        b[4] = Point3D(cx + radius/3, cy - radius, radius/2);
        b[5] = Point3D(cx + radius, cy - radius, radius/2);
        b[6] = Point3D(cx + radius, cy + radius, radius/2);
        b[7] = Point3D(cx + radius/3, cy + radius, radius/2);
        b[8] = Point3D(cx + radius/3, cy + radius/3, radius/2);
        b[9] = Point3D(cx - radius/3, cy + radius/3, radius/2);
        b[10] = Point3D(cx - radius/3, cy + radius, radius/2);
        b[11] = Point3D(cx - radius, cy + radius, radius/2);
    }

    void draw() {
        setcolor(5);
        for(int i = 1; i < n; i++) {
            line(a[i - 1].x, a[i - 1].y, a[i].x, a[i].y);
            if(i == n - 1) line(a[0].x, a[0].y, a[i].x, a[i].y);
            line(b[i - 1].x, b[i - 1].y, b[i].x, b[i].y);
            if(i == n - 1) line(b[0].x, b[0].y, b[i].x, b[i].y);
            line(b[i].x, b[i].y, a[i].x, a[i].y);
            if(i == n - 1) line(b[0].x, b[0].y, a[0].x, a[0].y);
        }

        for(int i = 0; i < n; i++) {
            fillellipse(a[i].x, a[i].y, 4, 4);
            fillellipse(b[i].x, b[i].y, 4, 4);
        }
    }
    void rotateY(int cx, int cy, int cz, int angle) {
        for(int i = 0; i < n; i++) {
            a[i].rotateY(cx, cy, cz, angle);
            b[i].rotateY(cx, cy, cz, angle);
        }
    }

    void rotateX(int cx, int cy, int cz, int angle) {
        for(int i = 0; i < n; i++) {
            a[i].rotateX(cx, cy, cz, angle);
            b[i].rotateX(cx, cy, cz, angle);
        }
    }

    void rotateZ(int cx, int cy, int cz, int angle) {
        for(int i = 0; i < n; i++) {
            a[i].rotateZ(cx, cy, cz, angle);
            b[i].rotateZ(cx, cy, cz, angle);
        }
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    Hache uno(centerX, centerY, 150);

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
