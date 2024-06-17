#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define WIDTH 500
#define HEIGHT 500

using namespace std;

void drawSierpinski(int depth, int x1, int y1, int x2, int y2, int x3, int y3) {
    if (depth == 0) {
        line(x1, y1, x2, y2);
        line(x2, y2, x3, y3);
        line(x3, y3, x1, y1);
    } else {
        int x12 = (x1 + x2) / 2;
        int y12 = (y1 + y2) / 2;
        int x23 = (x2 + x3) / 2;
        int y23 = (y2 + y3) / 2;
        int x31 = (x3 + x1) / 2;
        int y31 = (y3 + y1) / 2;

        drawSierpinski(depth - 1, x1, y1, x12, y12, x31, y31);
        drawSierpinski(depth - 1, x12, y12, x2, y2, x23, y23);
        drawSierpinski(depth - 1, x31, y31, x23, y23, x3, y3);
    }
}

int main() {
    //int gd = DETECT, gm;
    //initgraph(&gd, &gm, "");
    initwindow(800, 600);

    int depth = 5;
    int x1 = WIDTH / 2, y1 = 50;
    int x2 = 50, y2 = HEIGHT - 50;
    int x3 = WIDTH - 50, y3 = HEIGHT - 50;

    drawSierpinski(depth, x1, y1, x2, y2, x3, y3);

    while (!kbhit()) {
        delay(200);
    }

    closegraph();
    return 0;
}
