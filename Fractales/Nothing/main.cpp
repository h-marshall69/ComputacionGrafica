#include <iostream>
#include <winbgim.h>
#include <math.h>
using namespace std;

void getXY(int xini, int yini, int& x, int& y, int largo, float angulo) {
    x = xini + largo * sin(angulo * M_PI / 180);
    y = yini - largo * cos(angulo * M_PI / 180);
}

void draw1(int x1, int y1, int x8, int y8, bool val) {
        int dx = (x8 - x1)/3;
        int dy = (y8 - y1)/3;
        int x6 = x1 + dx;
        int y6 = y1 + dy;
        int x7 = x1 + 2*dx;
        int y7 = y1 + 2*dy;
        int x3 = ((x7 - x1)*cos(M_PI / 3) - (y1 - y7)*sin(M_PI / 3)) + x1;
        int y3 = ((x1 - x7)*sin(M_PI / 3) + (y7 - y1)*cos(M_PI / 3)) + y1;
        int x2 = (x1 + x3)/2;
        int y2 = (y1 + y3)/2;
        int x5 = x2 + dx*2;
        int y5 = y2 + dy*2;
        int x4 = x3 + dx;
        int y4 = y3 + dy;

        if (val) {
            line(x1, y1, x2, y2);
            line(x6, y6, x5, y5);
            line(x6, y6, x7, y7);
            line(x7, y7, x8, y8);
        } else {
            line(x1, y1, x6, y6);
            line(x6, y6, x7, y7);
            line(x2, y2, x7, y7);
            line(x5, y5, x8, y8);
        }

        line(x2, y2, x3, y3);
        line(x3, y3, x4, y4);
        line(x4, y4, x5, y5);
}

void draw(int x1, int y1, int x8, int y8, int n, int val) {
    if(n == 0) {
        draw1(x1, y1, x8, y8, val);
    } else {
        int dx = (x8 - x1)/3;
        int dy = (y8 - y1)/3;
        int x6 = x1 + dx;
        int y6 = y1 + dy;
        int x7 = x1 + 2*dx;
        int y7 = y1 + 2*dy;
        int x3 = ((x7 - x1)*cos(M_PI / 3) - (y1 - y7)*sin(M_PI / 3)) + x1;
        int y3 = ((x1 - x7)*sin(M_PI / 3) + (y7 - y1)*cos(M_PI / 3)) + y1;
        int x2 = (x1 + x3)/2;
        int y2 = (y1 + y3)/2;
        int x5 = x2 + dx*2;
        int y5 = y2 + dy*2;
        int x4 = x3 + dx;
        int y4 = y3 + dy;

        draw(x2, y2, x1, y1, n - 1, !val);
        draw(x2, y2, x3, y3, n - 1, !val);
        draw(x3, y3, x4, y4, n - 1, !val);
        draw(x4, y4, x5, y5, n - 1, !val);

        draw(x6, y6, x5, y5, n - 1, !val);

        draw(x7, y7, x6, y6, n - 1, !val);
        draw(x7, y7, x8, y8, n - 1, !val);
    }
}

void nothing(int x, int y, int l, int n) {
    draw(x - l, y + l/2, x + l, y + l/2, n, true);
}

int main() {
    initwindow(800, 600);

    int length = 250;
    int depth = 3;

    nothing(getmaxx()/2, getmaxy()/2, length, depth);

    getch();
    closegraph();
    return 0;
}
