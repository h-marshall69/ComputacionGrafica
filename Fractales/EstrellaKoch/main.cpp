#include <winbgim.h>
#include <cmath>
#include <iostream>

using namespace std;

void drawKochLine(int x1, int y1, int x2, int y2, int depth) {
    if (depth == 0) {
        line(x1, y1, x2, y2);
    } else {
        int dx = x2 - x1;
        int dy = y2 - y1;
        int x3 = x1 + dx / 3;
        int y3 = y1 + dy / 3;
        int x5 = x1 + 2 * dx / 3;
        int y5 = y1 + 2 * dy / 3;

        int x4 = x3 + (x5 - x3) * cos(M_PI / 3) - (y5 - y3) * sin(M_PI / 3);
        int y4 = y3 + (x5 - x3) * sin(M_PI / 3) + (y5 - y3) * cos(M_PI / 3);

        drawKochLine(x1, y1, x3, y3, depth - 1);
        drawKochLine(x3, y3, x4, y4, depth - 1);
        drawKochLine(x4, y4, x5, y5, depth - 1);
        drawKochLine(x5, y5, x2, y2, depth - 1);
    }
}

void drawSnowflake(int x, int y, int length, int depth) {
    int x1 = x - length / 2;
    int y1 = y + length * sqrt(3) / 6;
    int x2 = x + length / 2;
    int y2 = y + length * sqrt(3) / 6;
    int x3 = x;
    int y3 = y - length * sqrt(3) / 3;

    drawKochLine(x1, y1, x2, y2, depth);
    drawKochLine(x2, y2, x3, y3, depth);
    drawKochLine(x3, y3, x1, y1, depth);
}

int main() {
    int width = 800;
    int height = 600;
    initwindow(width, height);

    int length = 400; // Longitud inicial del lado del triángulo
    int depth = 1;    // Profundidad del fractal

    drawSnowflake(width / 2, height / 2, length, depth);

    getch();
    closegraph();
    return 0;
}
