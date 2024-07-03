#include <iostream>
#include <winbgim.h>
using namespace std;

void move(int direction, int step, int &x, int &y) {
    switch (direction) {
        case 1: y -= step; break;  // Up
        case 2: x += step; break;  // Right
        case 3: y += step; break;  // Down
        case 4: x -= step; break;  // Left
    }
    lineto(x, y);
}

void hilbert(int r, int d, int l, int u, int depth, int step, int &x, int &y) {
    if (depth > 0) {
        depth--;
        hilbert(d, r, u, l, depth, step, x, y);
        move(r, step, x, y);
        hilbert(r, d, l, u, depth, step, x, y);
        move(d, step, x, y);
        hilbert(r, d, l, u, depth, step, x, y);
        move(l, step, x, y);
        hilbert(u, l, d, r, depth, step, x, y);
    }
}

int main() {
    initwindow(800, 600);
    int step = 10;
    int depth = 3;
    int x = getmaxx() / 2 - step*depth*3;
    int y = getmaxy() / 2 - step*depth*3;


    moveto(x, y);

    hilbert(2, 3, 4, 1, depth, step, x, y);

    getch();
    closegraph();
    return 0;
}
