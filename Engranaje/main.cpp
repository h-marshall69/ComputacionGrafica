#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

void getXY(int xini, int yini, float angulo, int largo, int& x, int& y) {
    x = xini + largo * cos(angulo * M_PI / 180);
    y = yini - largo * sin(angulo * M_PI / 180);
}

void drawGear(int x, int y, int alfa, int r, int n, int col1) {
    float angulo = 360.0 / n;
    float angulo2 = 0;
    int x1, y1, x2, y2, x3, y3, x4, y4;
    setcolor(col1);
    circle(x, y, r);
    //circle(x, y, r/2);

    for (int i = 0; i < n; i++) {
        getXY(x, y, angulo2 + angulo / 5 + alfa, r, x1, y1);
        getXY(x, y, angulo2 + angulo / 3 + alfa, r + 30, x2, y2);
        getXY(x, y, angulo2 + 2 * angulo / 3 + alfa, r + 30, x3, y3);
        getXY(x, y, angulo2 + angulo - angulo / 5 + alfa, r, x4, y4);
        line(x1, y1, x2, y2);
        line(x2, y2, x3, y3);
        line(x3, y3, x4, y4);
        angulo2 += angulo;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int alfa = 0;
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    int dientes = 8;
    int radio = 80;

    while (!kbhit()) {
        drawGear(centerX, centerY, alfa, radio, dientes, 10);
        line(centerX, 0, centerX, getmaxy());
        line(0, centerY, getmaxx(), centerY);
        delay(100);
        drawGear(centerX, centerY, alfa, radio, dientes, 0);

        alfa++;
    }

    getch();
    closegraph();
    return 0;
}
