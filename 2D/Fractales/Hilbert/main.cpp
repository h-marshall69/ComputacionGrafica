#include <iostream>
#include <graphics.h>
#include <math.h>
#include <conio.h>
using namespace std;

void move(int j, int h, int &x, int &y) {
    if (j == 1) y -= h;
    else if (j == 2) x += h;
    else if (j == 3) y += h;
    else if (j == 4) x -= h;
    lineto(x, y);
}

void hilbert(int r, int d, int t, int u, int i, int h, int &x, int &y) {
    if (i > 0) {
        i--;
        hilbert(d, r, u, t, i, h, x, y);
        move(r, h, x, y);
        hilbert(r, d, t, u, i, h, x, y);
        move(d, h, x, y);
        hilbert(r, d, t, u, i, h, x, y);
        move(t, h, x, y);
        hilbert(u, t, d, r, i, h, x, y);
    }
}

int main() {
    int n, xl, yl;
    int x0 = 50, y0 = 150, x, y, h = 10;
    int r = 2, d = 3, t = 4, u = 1;
    int driver = DETECT, mode = 0;
    initgraph(&driver, &mode, "");


    x = x0;
    y = y0;
    moveto(x, y);
    hilbert(r, d, t, u, 4, h, x, y);

    getch();
    closegraph();
    return 0;
}
