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
    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

    // Método para rotar en el eje X
    void rotateX(double angle) {
        double y_new = y * cos(angle * M_PI / 180) - z * sin(angle * M_PI / 180);
        double z_new = y * sin(angle * M_PI / 180) + z * cos(angle * M_PI / 180);
        y = y_new;
        z = z_new;
    }

    // Método para rotar en el eje Y
    void rotateY(double angle) {
        double x_new = x * cos(angle * M_PI / 180) + z * sin(angle * M_PI / 180);
        double z_new = -x * sin(angle * M_PI / 180) + z * cos(angle * M_PI / 180);
        x = x_new;
        z = z_new;
    }

    // Método para rotar en el eje Z
    void rotateZ(double angle) {
        double x_new = x * cos(angle * M_PI / 180) - y * sin(angle * M_PI / 180);
        double y_new = x * sin(angle * M_PI / 180) + y * cos(angle * M_PI / 180);
        x = x_new;
        y = y_new;
    }

    // Método para rotar en un punto de referencia (cx, cy)
    void rotate(double cx, double cy, double angle) {
        // Translate to the origin
        x -= cx;
        y -= cy;

        // Perform rotation
        rotateY(angle);

        // Translate back
        x += cx;
        y += cy;
    }
};


int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    Point3D a(100, 100, 0);
    Point3D b(200, 100, 0);
    Point3D c(100, 200, 0);
    Point3D d(200, 200, 0);

    while (!kbhit()) {
        cleardevice();
        line(a.x, a.y, b.x, b.y);
        line(b.x, b.y, d.x, d.y);
        line(c.x, c.y, d.x, d.y);
        line(a.x, a.y, c.x, c.y);
        a.rotate(150, 150, 1);
        b.rotate(150, 150, 1);
        c.rotate(150, 150, 1);
        d.rotate(150, 150, 1);
        delay(60);
        line(a.x, a.y, b.x, b.y);
        line(b.x, b.y, d.x, d.y);
        line(c.x, c.y, d.x, d.y);
        line(a.x, a.y, c.x, c.y);
    }
    getch();
    closegraph();
    return 0;
}
