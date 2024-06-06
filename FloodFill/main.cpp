#include <graphics.h>
#include <iostream>
#include <utility>
#include <stack>
#include <queue>
using namespace std;

void FloodFillTwo(int x, int y, int fillColor, int oldColor) {
    if(0 < x && x < getmaxx() && 0 < y && y < getmaxy()) {
        if(getpixel(x, y) == oldColor) {
            putpixel(x, y, fillColor);
            FloodFillTwo(x + 1, y, fillColor, oldColor);
            FloodFillTwo(x - 1, y, fillColor, oldColor);
            FloodFillTwo(x, y + 1, fillColor, oldColor);
            FloodFillTwo(x, y - 1, fillColor, oldColor);
        }
    }
}

void FloodFillExploration(int x, int y, int fillColor, int oldColor) {
    queue<pair<int, int>> pixels;
    pixels.push(make_pair(x, y));

    while (!pixels.empty()) {
        pair<int, int> current = pixels.front();
        pixels.pop();
        x = current.first;
        y = current.second;

        if (x >= 0 && x < getmaxx() && y >= 0 && y < getmaxy() && getpixel(x, y) == oldColor) {
            putpixel(x, y, fillColor);

            // Explorar los píxeles adyacentes
            pixels.push(make_pair(x + 1, y));
            pixels.push(make_pair(x - 1, y));
            pixels.push(make_pair(x, y + 1));
            pixels.push(make_pair(x, y - 1));
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
    while(!kbhit()) {
        if(mousex() > 0 && mousex() < 200 && mousey() > 0 && mousey() < 50) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                colorUno = getpixel(x, y);
            }
        }
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            setfillstyle(SOLID_FILL, colorUno);
            colorDos = getpixel(x, y);
            FloodFillExploration(x, y, colorUno, colorDos);
        }
    }
    getch();
    closegraph();
    return 0;
}
