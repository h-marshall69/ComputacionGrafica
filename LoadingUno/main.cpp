
#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

void getXY(int xini, int yini, float angulo, int largo, int& x, int& y) {
    x = xini + largo * cos(angulo * M_PI / 180);
    y = yini - largo * sin(angulo * M_PI / 180);
}

void loading(int x, int y, int r, int actual, int n, int col1 = 10) {
    float angulo = 360.0 / n;
    float angulo2 = 0;
    int x1, y1;
    for (int i = 0; i <= actual; i++) {
        getXY(x, y, angulo2, r, x1, y1);
        setcolor(col1);
        circle(x1, y1, 5);
        angulo2 += angulo;
    }
}
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    setcolor(10);

    int radius = 50;
    int startAngle = 0;
    int endAngle = 30;
    int increment = 10;
    int actual = 0;

    outtextxy(centerX - 30, centerY - 5, "Loading...");
    while (!kbhit()) {

        loading(centerX, centerY, radius, actual, 12);

        delay(100);
        loading(centerX, centerY, radius, actual, 12, 0);
        actual++;
        actual=actual%12;

    }

    closegraph();
    return 0;
}
