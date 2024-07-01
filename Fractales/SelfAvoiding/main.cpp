#include <iostream>
#include <winbgim.h>
#include <math.h>
using namespace std;

void draw1(int x1, int y1, int x8, int y8) {
        int dx = (x8 - x1)/3;
        int dy = (y8 - y1)/3;

        int x2 = x1 + dx;
        int y2 = y1 + dy;

        int x4 = ((x2 - x1)*cos(M_PI / 3) - (y1 - y2)*sin(M_PI / 3)) + x1;
        int y4 = ((x1 - x2)*sin(M_PI / 3) + (y2 - y1)*cos(M_PI / 3)) + y1;

        int x3 = x4 + dx;
        int y3 = y4 + dy;

        int x6 = ((x3 - x4)*cos(M_PI / 3) - (y4 - y3)*sin(M_PI / 3)) + x4;
        int y6 = ((x4 - x3)*sin(M_PI / 3) + (y3 - y4)*cos(M_PI / 3)) + y4;

        int x7 = x6 + dx;
        int y7 = y6 + dy;

        int x5 = x6 - dx;
        int y5 = y6 - dy;

        x8 = x3 + dx;
        y8 = y3 + dy;
        line(x1, y1, x2, y2);
        line(x3, y3, x2, y2);
        line(x4, y4, x3, y3);
        line(x4, y4, x5, y5);
        line(x5, y5, x6, y6);
        line(x6, y6, x7, y7);
        line(x8, y8, x7, y7);
}

void draw(int x1, int y1, int x8, int y8, int n) {
    if(n == 0) {
        draw1(x1, y1, x8, y8);
    } else {
        int dx = (x8 - x1)/3;
        int dy = (y8 - y1)/3;

        int x2 = x1 + dx;
        int y2 = y1 + dy;

        int x4 = ((x2 - x1)*cos(M_PI / 3) - (y1 - y2)*sin(M_PI / 3)) + x1;
        int y4 = ((x1 - x2)*sin(M_PI / 3) + (y2 - y1)*cos(M_PI / 3)) + y1;

        int x3 = x4 + dx;
        int y3 = y4 + dy;

        int x6 = ((x3 - x4)*cos(M_PI / 3) - (y4 - y3)*sin(M_PI / 3)) + x4;
        int y6 = ((x4 - x3)*sin(M_PI / 3) + (y3 - y4)*cos(M_PI / 3)) + y4;

        int x7 = x6 + dx;
        int y7 = y6 + dy;

        int x5 = x6 - dx;
        int y5 = y6 - dy;

        draw(x1, y1, x2, y2, n - 1);
        draw(x3, y3, x2, y2, n - 1);
        draw(x4, y4, x3, y3, n - 1);
        draw(x4, y4, x5, y5, n - 1);
        draw(x5, y5, x6, y6, n - 1);
        //draw(x6, y6, x7, y7, n - 1);
        //draw(x8, y8, x7, y7, n - 1);
    }
}

void nothing(int x, int y, int l, int n) {
    draw(x - l, y + l/2, x + l, y + l/2, n);
    //draw1(x - l, y + l/2, x + l, y + l/2);
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
