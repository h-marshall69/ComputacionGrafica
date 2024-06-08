#include <graphics.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <string>
using namespace std;

class Point3D {
public:
    double x;
    double y;
    double z;

    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    void rotateX(double cx, double cy, double cz, double angle) {
        double rad = angle * M_PI / 180;
        double temp = ((y - cy) * cos(rad) - (z - cz) * sin(rad)) + cy;
        z = ((y - cy) * sin(rad) + (z - cz) * cos(rad)) + cz;
        y = temp;
    }

    void rotateY(double cx, double cy, double cz, double angle) {
        double rad = angle * M_PI / 180;
        double temp = ((x - cx) * cos(rad) + (z - cz) * sin(rad)) + cx;
        z = (-(x - cx) * sin(rad) + (z - cz) * cos(rad)) + cz;
        x = temp;
    }

    void rotateZ(double cx, double cy, double cz, double angle) {
        double rad = angle * M_PI / 180;
        double temp = ((x - cx) * cos(rad) - (y - cy) * sin(rad)) + cx;
        y = ((x - cx) * sin(rad) + (y - cy) * cos(rad)) + cy;
        x = temp;
    }
};

int main() {
    srand(time(0));

    std::vector<Point3D> stars;
    for (int i = 0; i < 150; ++i) {
        stars.push_back(Point3D(rand() % 2001 - 1000, rand() % 2001 - 1000, rand() % 2001 - 1000));
    }

    Point3D spaceship(0, 0, -1300);

    int gd = DETECT, gm;
    //initgraph(&gd, &gm, "");
    initwindow(800,600);


    while (true) {
        cleardevice();
        setcolor(WHITE);

        string positionx = "X: " + to_string(spaceship.x);
        char *cstrx = new char[positionx.length() + 1];
        strcpy(cstrx, positionx.c_str());
        outtextxy(10, 10, cstrx);
        delete[] cstrx;

        string positiony = "Y: " + to_string(spaceship.y);
        char *cstry = new char[positiony.length() + 1];
        strcpy(cstry, positiony.c_str());
        outtextxy(10, 30, cstry);
        delete[] cstry;

        string positionz = "Z: " + to_string(spaceship.z);
        char *cstrz = new char[positionz.length() + 1];
        strcpy(cstrz, positionz.c_str());
        outtextxy(10, 50, cstrz);
        delete[] cstrz;

        outtextxy(getmaxx() - 140, getmaxy() - 70, "Move");
        outtextxy(getmaxx() - 150, getmaxy() - 50, "Q   W   E");
        outtextxy(getmaxx() - 150, getmaxy() - 30, "A    S    D");

        for (const auto& star : stars) {
            double dx = star.x - spaceship.x;
            double dy = star.y - spaceship.y;
            double dz = star.z - spaceship.z;

            if (dz > 0) {
                int screenX = 320 + dx / (dz / 100 + 1);
                int screenY = 240 + dy / (dz / 100 + 1);
                int size = std::max(1, 5 - static_cast<int>(dz / 100));
                float brightness = 1 - star.z / getmaxx();
                int color = 15 * brightness;
                setcolor(color);
                fillellipse(screenX, screenY, size, size);
            }
        }

        if (kbhit()) {
            char key = getch();
            if (key == 'w' || key == 'W') {
                spaceship.z += 10;
            } else if (key == 's' || key == 'S') {
                spaceship.z -= 10;
            } else if (key == 'a' || key == 'A') {
                spaceship.x -= 10;
            } else if (key == 'd' || key == 'D') {
                spaceship.x += 10;
            } else if (key == 'q' || key == 'Q') {
                spaceship.y += 10;
            } else if (key == 'e' || key == 'E') {
                spaceship.y -= 10;
            } else {
                closegraph();
                return 0;
            }
        }

        delay(16);
    }

    closegraph();
    return 0;
}
