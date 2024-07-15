#include <iostream>
#include <winbgim.h>
#include <math.h>
using namespace std;

void getXY(int xini, int yini, int& x, int& y, int largo, float angulo) {
    x = xini + largo * sin(angulo * M_PI / 180);
    y = yini - largo * cos(angulo * M_PI / 180);
}

void nose(int x1, int y1, int x2, int y2, int n){
    if(n == 0) {
        line(x2, y2, x1, y1);
    } else {
        int dx = x2 - x1;
        int dy = y2 - y1;

        int x3 = x1 + dx / 3;
        int y3 = y1 + dy / 3;

        int x5 = x1 + 2 * dx / 3;
        int y5 = y1 + 2 * dy / 3;

        int x4 = ((x5 - x3)*cos(M_PI / 3) - (y3 - y5)*sin(M_PI / 3)) + x3;
        int y4 = ((x3 - x5)*sin(M_PI / 3) + (y5 - y3)*cos(M_PI / 3)) + y3;

        nose(x1, y1, x3, y3, n - 1);
        nose(x3, y3, x4, y4, n - 1);
        nose(x4, y4, x5, y5, n - 1);
        nose(x5, y5, x2, y2, n - 1);
    }
}

void drawKochLine(int x, int y, int l, int n) {
    int x2, y2;
    getXY(x - l, y + l, x2, y2, l*2, 30);
    nose(x + l, y + l/2,x - l, y + l/2,  n);
    nose(x - l, y + l/2, x2, y2 -l/2, n);
    nose(x2, y2 - l/2, x + l, y + l/2, n);
}

int main() {
    initwindow(800, 600);

    int length = 200;
    int depth = 4;
    line(getmaxx()/2, 0, getmaxx()/2, getmaxy());

    drawKochLine(getmaxx()/2, getmaxy()/2, length, depth);

    getch();
    closegraph();
    return 0;
}
