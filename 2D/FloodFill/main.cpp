#include <graphics.h>
#include <iostream>
#include <utility>
#include <queue>

using namespace std;

void Fillqueue(int x, int y, int fillColor, int oldColor) {
    queue<pair<int, int>> pixels;
    pixels.push(make_pair(x, y));

    while (!pixels.empty()) {
        pair<int, int> current = pixels.front();
        pixels.pop();
        x = current.first;
        y = current.second;

        if (0 <= x && x <= getmaxx() && 0 <= y && y <= getmaxy()) {
            if (getpixel(x, y) == oldColor) {
                putpixel(x, y, fillColor);
            }
            if (getpixel(x + 1, y) == oldColor) {
                putpixel(x + 1, y, fillColor);
                pixels.push(make_pair(x + 1, y));
            }
            if (getpixel(x - 1, y) == oldColor) {
                putpixel(x - 1, y, fillColor);
                pixels.push(make_pair(x - 1, y));
            }
            if (getpixel(x, y + 1) == oldColor) {
                putpixel(x, y + 1, fillColor);
                pixels.push(make_pair(x, y + 1));
            }
            if (getpixel(x, y - 1) == oldColor) {
                putpixel(x, y - 1, fillColor);
                pixels.push(make_pair(x, y - 1));
            }
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    circle(centerX, centerY, 100);

    setcolor(YELLOW);
    line(centerX, centerY, 250, 200);
    int colorUno = BLACK, colorDos = BLACK;

    setfillstyle(SOLID_FILL, YELLOW);
    bar(0, 0, 50, 50);
    setfillstyle(SOLID_FILL, BLACK);
    bar(50, 0, 100, 50);
    setfillstyle(SOLID_FILL, RED);
    bar(100, 0, 150, 50);
    setfillstyle(SOLID_FILL, BLUE);
    bar(150, 0, 200, 50);

    int x, y;
    while (!kbhit()) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x > 0 && x < 200 && y > 0 && y < 50) {
                colorUno = getpixel(x, y);
            } else {
                setfillstyle(SOLID_FILL, colorUno);
                colorDos = getpixel(x, y);
                Fillqueue(x, y, colorUno, colorDos);
            }
        }
        delay(100);
    }

    getch();
    closegraph();
    return 0;
}
