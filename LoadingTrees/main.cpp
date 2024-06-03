#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

void getXY(int xini, int yini, float angulo, int largo, int& x, int& y) {
    x = xini + largo * cos(angulo * M_PI / 180);
    y = yini - largo * sin(angulo * M_PI / 180);
}

void loadingUno(int x, int y, int r, int n, float alfa, int actual, int col1, int col2) {
    float angulo = 360.0 / n;
    float angulo2 = 0;
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++) {
        getXY(x, y, angulo2 + alfa, r, x1, y1);
        getXY(x, y, angulo2 + alfa, r + 20, x2, y2);
        setcolor(col1);
        if (i != actual)
            line(x1, y1, x2, y2);
        angulo2 += angulo;
    }
    getXY(x, y, angulo * actual + alfa, r, x1, y1);
    getXY(x, y, angulo * actual + alfa, r + 20, x2, y2);
    setcolor(col2);
    line(x1, y1, x2, y2);
}


int main() {
    initwindow(800, 600);

    int actual = 0;
    float alfa = 0.0;
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    outtextxy(centerX - 30, centerY - 5, "Loading...");
    while (true) {
        loadingUno(centerX, centerY, 50, 12, alfa, actual, 15, 10);
        delay(100);
        loadingUno(centerX, centerY, 50, 12, alfa, actual, 15, 0);
        actual = (actual + 1) % 12;
        //alfa ++;
    }

    getch();
    closegraph();
    return 0;
}
