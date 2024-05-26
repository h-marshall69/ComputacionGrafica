#include <iostream>
#include <winbgim.h>
#include <math.h>
#include <list>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

using namespace std;
class Point{
public:
    double x, y;
    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}
    Point operator+(const Point p) {
        return Point(this->x + p.x, this->y + p.y);
    }
    Point operator-(const Point p) {
        return Point(this->x - p.x, this->y - p.y);
    }
};
class Particle{
public:
    Point pos;
    Point acel;
    Point vel;
    double radio;
    Particle(Point p, double radio = 25.0): pos(p), radio(radio) {
        this->vel = Point(1.0, 1.0);
        this->acel = Point(0.0, -0.5);
    }
    void draw() {
        circle(pos.x, pos.y, radio);
    }

    void update() {
        //vel = vel - acel;
        pos = pos + vel;
    }

    void collision() {
        if(pos.x - radio <= 0 || pos.x + radio >= getmaxx())
            vel.x = -vel.x;
        if(pos.y - radio <= 0 || pos.y + radio >= getmaxy())
            vel.y = -vel.y;
    }
};

class Kdtree{
public:
    list<Particle> root;
    void add(double x = 0.0, double y = 0.0, double r = 0.0) {
        root.push_front(Particle(Point(x, y), r));
    }

};

int main() {
    srand(time(0));
    Kdtree k;
    //k.add(100, 550, 25);
    for (int i = 0; i < 25; ++i) {
        double x = (rand() + 50) % 750; // Generar x aleatorio entre 0 y 799
        double y = (rand() + 50) % 550; // Generar y aleatorio entre 0 y 599
        k.add(x, y, 20);
    }
    initwindow(800,600);
    bool tm = true;
    while(!kbhit()){
        for(auto &r: k.root) {
            r.draw();
            r.update();
            r.collision();

        }
        delay(16);
            cleardevice();
    }
    getch();
    closegraph();
    return 0;
}
