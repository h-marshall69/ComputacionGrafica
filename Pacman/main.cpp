#include <iostream>
#include <winbgim.h>
#include <math.h>
void linea(int xini, int yini, float angulo, int largo) {
    int x, y;
    x = largo*cos(angulo*M_PI/180) + xini;
    y = largo*sin(angulo*M_PI/180) + yini;
    line(xini, yini, x, y);
}

void getXY(int xini, int yini, float angulo, int largo, int &x, int &y) {
    x = largo*cos(angulo*M_PI/180) + xini;
    y = largo*sin(angulo*M_PI/180) + yini;
}

void pollito(int x, int y, int e) {
    circle(x + 3*e, y+3*e, 3*e);
    int x1, y1;
    int x2, y2;
    getXY(x + 3*e, y+3*e, 250, 3*e, x1, y1);
    getXY(x + 3*e, y+3*e, 245, 4*e, x2, y2);
    line(x1, y2, x2, y2);

    getXY(x + 3*e, y+3*e, 275, 3*e, x1, y1);
    getXY(x + 3*e, y+3*e, 280, 4*e, x2, y2);
    line(x1, y2, x2, y2);
}

void pacman(int x, int y, int e) {
    arc(x+3*e, y+3*e, 30, 330, 3*e);
    linea(x+3*e, y+3*e, 30, 3*e);
    linea(x+3*e, y+3*e, 330, 3*e);
}
int main() {
    initwindow(800,800);
    int e = 22;
    pollito(400, 300, 25);
    //pacman(400,400, e);
    getch();
    closegraph();
    return 0;
}
