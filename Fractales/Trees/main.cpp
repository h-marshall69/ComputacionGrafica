#include <iostream>
#include <winbgim.h>
#include <math.h>
using namespace std;

void getXY(int xini, int yini, float angulo, int largo, int& x, int& y) {
    x = xini + largo * sin(angulo * M_PI / 180);
    y = yini - largo * cos(angulo * M_PI / 180);
}

void Arbol(int x, int y, int l, double angulo, int n) {
    int x2;
    int y2;
    getXY(x, y, angulo, l, x2, y2);
    line(x, y, x2, y2);

    if(n > 0) {
        Arbol(x2, y2, l * 2 / 3, angulo + 45, n - 1);
        Arbol(x2, y2, l * 2 / 3, angulo - 45, n - 1);
    }
}

int main() {
    initwindow(800, 600);
    int large = 200;

    Arbol(getmaxx() / 2, getmaxy(), large, 0, 10);

    getch();
    closegraph();
    return 0;
}