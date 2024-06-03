#include <iostream>
#include <vector>
#include <winbgim.h>
#include <cmath>
using namespace std;

void linea(int xini, int yini, float angulo, int largo) {
    int x, y;
    x = largo * cos(angulo * M_PI / 180) + xini;
    y = largo * sin(angulo * M_PI / 180) + yini;
    line(xini, yini, x, y);
}

void getXY(int xini, int yini, float angulo, int largo, int &x, int &y) {
    x = largo * cos(angulo * M_PI / 180) + xini;
    y = largo * sin(angulo * M_PI / 180) + yini;
}

class Point {
public:
    double x, y;
    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}
};

class Pacman {
public:
    Point position;
    Point velocity;

    int radius;
    float angulo;
    int inc;

    Pacman(double x, double y, double vx, double vy): position(x, y), velocity(vx, vy) {
        angulo = 0;
        inc = 1;
        radius = 20;
    }

    void mover() {
        position.x += velocity.x;
        position.y += velocity.y;
        angulo += inc;
        if (position.x - radius < 0 || position.x + radius > 800)
            velocity.x = -velocity.x;
        if (position.y - radius < 0 || position.y + radius > 600)
            velocity.y = -velocity.y;

        if (angulo < 0 || angulo > 45)
            inc = -inc;
    }

    void graficar(int color) {
        setcolor(color);
        arc(position.x , position.y , angulo, 360 - angulo, radius);
        linea(position.x, position.y, angulo, radius);
        linea(position.x, position.y, 360 - angulo, radius);
    }
};

int main() {
    initwindow(800, 600);
    vector<Pacman> pacmans;

    pacmans.push_back(Pacman(500.0, 400.0, 1.0, -1.0));
    pacmans.push_back(Pacman(100.0, 200.0, -1.0, 1.0));

    while (!kbhit()) {
        for (auto &pacman : pacmans) {
            pacman.graficar(RED); // Puedes cambiar el color si quieres
            pacman.mover();
        }
        delay(16);
        cleardevice();
    }

    getch();
    closegraph();
    return 0;
}
