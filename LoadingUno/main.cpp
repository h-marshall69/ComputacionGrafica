#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

void getXY(int xini, int yini, float angulo, int largo, int& x, int& y) {
    cout << xini << "::" << yini << endl;
    x = xini + largo * cos(angulo * M_PI / 180);
    y = yini - largo * sin(angulo * M_PI / 180);
    cout << x << ":" << y << endl;
}

void loading(int x, int y, int r, int actual, int n, int col1 = 10, int col2 = 0) {
    float angulo = 360.0 / n;
    float angulo2 = 0;
    int x1, y1;
    for (int i = 0; i < n; i++) {
        getXY(x, y, angulo2, r, x1, y1);
        setcolor(i <= actual ? col1 : col2);
        circle(x1, y1, 5);
        angulo2 += angulo;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    int radius = 50;
    int actual = 0;
    int numDots = 12;
    int delayTime = 100;


    outtextxy(centerX - 30, centerY - 5, "Loading...");

    while (!kbhit()) {
        loading(centerX, centerY, radius, actual, numDots);
        break;
        delay(delayTime);
        loading(centerX, centerY, radius, actual, numDots, 0);
        actual = (actual + 1) % numDots;

    }

    closegraph();
    return 0;
}
