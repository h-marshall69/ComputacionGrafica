#include <graphics.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void getXY(int xini, int yini, float angulo, int largo, int& x, int& y) {
    constexpr float DEG2RAD = M_PI / 180.0f;
    x = xini + largo * cos(angulo * DEG2RAD);
    y = yini - largo * sin(angulo * DEG2RAD);
}

class Point3D {
public:
    double x;
    double y;
    double z;

    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    void rotateX(int cx, int cy, int cz, double angle) {
        double rad = angle * M_PI / 180.0;
        double temp = ((y - cy) * cos(rad) - (z - cz) * sin(rad)) + cy;
        z = ((y - cy) * sin(rad) + (z - cz) * cos(rad)) + cz;
        y = temp;
    }

    void rotateY(int cx, int cy, int cz, double angle) {
        double rad = angle * M_PI / 180.0;
        double temp = ((x - cx) * cos(rad) + (z - cz) * sin(rad)) + cx;
        z = (-(x - cx) * sin(rad) + (z - cz) * cos(rad)) + cz;
        x = temp;
    }

    void rotateZ(int cx, int cy, int cz, double angle) {
        double rad = angle * M_PI / 180.0;
        double temp = ((x - cx) * cos(rad) - (y - cy) * sin(rad)) + cx;
        y = ((x - cx) * sin(rad) + (y - cy) * cos(rad)) + cy;
        x = temp;
    }
};

class Gear {
public:
    vector<Point3D> a;
    vector<Point3D> b;
    vector<Point3D> aa;
    vector<Point3D> bb;

    Gear(int cx, int cy, int radius) {
        a.emplace_back(cx - radius, cy - radius, 0);
        a.emplace_back(cx - radius/3, cy - radius, 0);
        a.emplace_back(cx + radius, cy + radius, 0);
        a.emplace_back(cx + radius/3, cy + radius, 0);

        aa.emplace_back(cx + radius, cy - radius, 0);
        aa.emplace_back(cx + radius/3, cy - radius, 0);
        aa.emplace_back(cx - radius, cy + radius, 0);
        aa.emplace_back(cx - radius/3, cy + radius, 0);

        b.emplace_back(cx - radius, cy - radius, radius / 2);
        b.emplace_back(cx - radius/3, cy - radius, radius / 2);
        b.emplace_back(cx + radius, cy + radius, radius / 2);
        b.emplace_back(cx + radius/3, cy + radius, radius / 2);

        bb.emplace_back(cx + radius, cy - radius, radius / 2);
        bb.emplace_back(cx + radius/3, cy - radius, radius / 2);
        bb.emplace_back(cx - radius, cy + radius, radius / 2);
        bb.emplace_back(cx - radius/3, cy + radius, radius / 2);

    }

    void draw() {
        setcolor(5);

        for (size_t i = 1; i < a.size(); i++) {
            line(a[i - 1].x, a[i - 1].y, a[i].x, a[i].y);
            if (i == a.size() - 1) line(a[0].x, a[0].y, a[i].x, a[i].y);
            line(b[i - 1].x, b[i - 1].y, b[i].x, b[i].y);
            if (i == a.size() - 1) line(b[0].x, b[0].y, b[i].x, b[i].y);
            line(b[i].x, b[i].y, a[i].x, a[i].y);
            if (i == a.size() - 1) line(b[0].x, b[0].y, a[0].x, a[0].y);
        }

        for (size_t i = 1; i < aa.size(); i++) {
            line(aa[i - 1].x, aa[i - 1].y, aa[i].x, aa[i].y);
            if (i == aa.size() - 1) line(aa[0].x, aa[0].y, aa[i].x, aa[i].y);
            line(bb[i - 1].x, bb[i - 1].y, bb[i].x, bb[i].y);
            if (i == aa.size() - 1) line(bb[0].x, bb[0].y, bb[i].x, bb[i].y);
            line(bb[i].x, bb[i].y, aa[i].x, aa[i].y);
            if (i == aa.size() - 1) line(bb[0].x, bb[0].y, aa[0].x, aa[0].y);
        }

        for (const auto& aa2 : a) {
            fillellipse(aa2.x, aa2.y, 4, 4);
        }

        for (const auto& bb2 : b) {
            fillellipse(bb2.x, bb2.y, 4, 4);
        }

        for (const auto& aa1 : aa) {
            fillellipse(aa1.x, aa1.y, 4, 4);
        }

        for (const auto& bb1 : bb) {
            fillellipse(bb1.x, bb1.y, 4, 4);
        }
    }

    void rotateY(int cx, int cy, int cz, int angle) {
        for (auto& point : a) point.rotateY(cx, cy, cz, angle);
        for (auto& point : b) point.rotateY(cx, cy, cz, angle);
        for (auto& point : aa) point.rotateY(cx, cy, cz, angle);
        for (auto& point : bb) point.rotateY(cx, cy, cz, angle);
    }

    void rotateX(int cx, int cy, int cz, int angle) {
        for (auto& point : a) point.rotateX(cx, cy, cz, angle);
        for (auto& point : b) point.rotateX(cx, cy, cz, angle);
        for (auto& point : aa) point.rotateX(cx, cy, cz, angle);
        for (auto& point : bb) point.rotateX(cx, cy, cz, angle);
    }

    void rotateZ(int cx, int cy, int cz, int angle) {
        for (auto& point : a) point.rotateZ(cx, cy, cz, angle);
        for (auto& point : b) point.rotateZ(cx, cy, cz, angle);
        for (auto& point : aa) point.rotateZ(cx, cy, cz, angle);
        for (auto& point : bb) point.rotateZ(cx, cy, cz, angle);
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    Gear uno(centerX, centerY, 150);

    while (true) {
        cleardevice();

        if (kbhit()) {
            char key = getch();
            switch (key) {
                case 'a': case 'A': uno.rotateY(centerX, centerY, 0, -1); break;
                case 'd': case 'D': uno.rotateY(centerX, centerY, 0, 1); break;
                case 'w': case 'W': uno.rotateX(centerX, centerY, 0, 1); break;
                case 's': case 'S': uno.rotateX(centerX, centerY, 0, -1); break;
                case 'q': case 'Q': uno.rotateZ(centerX, centerY, 0, 1); break;
                case 'e': case 'E': uno.rotateZ(centerX, centerY, 0, -1); break;
                default: closegraph(); return 0;
            }
        }

        uno.draw();
        delay(16);
    }

    closegraph();
    return 0;
}
