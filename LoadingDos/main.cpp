#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

void getXY(int xini, int yini, float angulo, int largo, int& x, int& y) {
    x = xini + largo * cos(angulo * M_PI / 180);
    y = yini - largo * sin(angulo * M_PI / 180);
}

void loading(int x, int y, int radius, int actual, int alfa, int n, int col1, int &dis) {
    float angulo = 360.0 / n;
    float angulo2 = 0;
    int x1, y1;
    for (int i = 0; i < n; i++) {
        if(i%2 == 0)
            getXY(x, y, angulo2 + alfa, radius + dis, x1, y1);
        else
            getXY(x, y, angulo2 + alfa, radius - dis, x1, y1);
        setcolor(col1);
        circle(x1, y1, 7);
        angulo2 += angulo;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    int radius = 80;
    int actual = 0;
    int alfa = 0;
    int dis = 0;
    int direction = 1;

    outtextxy(centerX - 30, centerY - 5, "Loading...");

    while (!kbhit()) {
        loading(centerX, centerY, radius, actual, alfa, 12, 10, dis);
        delay(100);
        loading(centerX, centerY, radius, actual, alfa, 12, 0, dis);
        actual = (actual + 1) % 12;
        if (dis >= 10 || dis <= -10)
            direction = -direction;
        dis += direction;
        alfa++;
    }

    closegraph();
    return 0;
}
