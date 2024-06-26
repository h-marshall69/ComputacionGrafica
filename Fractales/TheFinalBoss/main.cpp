#include <winbgim.h>
#include <iostream>
#include <cmath>
using namespace std;

void drawTriangle(int x, int y, int l, int n, int thickness) {
    //setlinestyle(SOLID_LINE, 0, thickness);
    line(x, y - l, x, y);
    //bar(x - thickness, y - l, x + thickness, y);
    line(x, y, x - l, y + l / 2);
    line(x, y, x + l, y + l / 2);
    if (n > 0) {
        drawTriangle(x, y - l, l / 2, n - 1, thickness - 2);
        drawTriangle(x - l, y + l / 2, l / 2, n - 1, thickness - 2);
        drawTriangle(x + l, y + l / 2, l / 2, n - 1, thickness - 2);
    }
}


int main() {
    initwindow(800, 600);
    int large = 150;
    int n = 5;

    drawTriangle(getmaxx()/2, getmaxy()/2 + large/2, large, n, n * 2);

    getch();
    closegraph();

    return 0;
}
