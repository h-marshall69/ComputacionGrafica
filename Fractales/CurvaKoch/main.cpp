#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

void drawKochCurve(int depth, int x1, int y1, int x2, int y2) {
    if (depth == 0) {
        line(x1, y1, x2, y2);
    } else {
        int deltaX = x2 - x1;
        int deltaY = y2 - y1;

        int x3 = x1 + deltaX / 3;
        int y3 = y1 + deltaY / 3;

        int x4 = x1 + 2 * deltaX / 3;
        int y4 = y1 + 2 * deltaY / 3;

        int xMid = (x1 + x2) / 2;
        int yMid = (y1 + y2) / 2;

        int x5 = (x3 + x4) / 2 + (y3 - y4) * sqrt(3) / 6;
        int y5 = (y3 + y4) / 2 + (x4 - x3) * sqrt(3) / 6;

        drawKochCurve(depth - 1, x1, y1, x3, y3);
        drawKochCurve(depth - 1, x3, y3, x5, y5);
        drawKochCurve(depth - 1, x5, y5, x4, y4);
        drawKochCurve(depth - 1, x4, y4, x2, y2);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int depth = 4; // Profundidad de la curva de Koch

    // Coordenadas iniciales para la línea base de la curva de Koch
    int x1 = 100, y1 = 300;
    int x2 = 700, y2 = 300;

    drawKochCurve(depth, x1, y1, x2, y2);

    while (!kbhit()) {
        delay(200);
    }

    closegraph();
    return 0;
}
