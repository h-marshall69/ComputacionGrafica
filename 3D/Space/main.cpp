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
                int screenX = 400 + dx / (dz / 100 + 1);
                int screenY = 300 + dy / (dz / 100 + 1);
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
            }else if (key == 'x' || key == 'X') {
                for (auto& star : stars) {
                    star.rotateX(spaceship.x, spaceship.y, spaceship.z, 1);
                }
            }else if (key == 'y' || key == 'y') {
                for (auto& star : stars) {
                    star.rotateY(spaceship.x, spaceship.y, spaceship.z, 1);
                }
            }else if (key == 'z' || key == 'Z') {
                for (auto& star : stars) {
                    star.rotateZ(spaceship.x, spaceship.y, spaceship.z, 1);
                }
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
