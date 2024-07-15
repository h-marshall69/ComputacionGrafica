#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

const int H_N_C = CYAN;
const int S_N_C = RED;
const int M_N_C = LIGHTRED;

void drawClockFace(int cx, int cy, int radius) {
    setcolor(WHITE);
    circle(cx, cy, 3);
    for (int i = 0; i < 9; i++)
        circle(cx, cy, radius + 13 + i);

    for (int i = 0; i < 12; i++) {
        float angle = i * (M_PI / 6);
        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);
        circle(x, y, 2);
        circle(x + 5, y, 0);
        circle(x - 5, y, 0);
        circle(x, y + 5, 0);
        circle(x, y - 5, 0);
    }

    for (int i = 0; i < 360; i += 6)
        putpixel(cx + radius * cos(i * (M_PI / 180)), cy + radius * sin(i * (M_PI / 180)), DARKGRAY);
}

void getXY(int xini, int yini, float angle, int length, int& x, int& y) {
    x = xini + length * cos(angle);
    y = yini - length * sin(angle);
}

void drawClock(int cx, int cy, int radius, int hours, int minutes, int seconds) {
    float secondAngle = (-seconds) * (M_PI / 30) + (M_PI / 2);
    float minuteAngle = (-minutes) * (M_PI / 30) + (M_PI / 2);
    float hourAngle = (-hours % 12 + minutes / 60.0) * (M_PI / 6) + (M_PI / 2);

    int x1, y1;
    int x2, y2;
    int x3, y3;
    setcolor(H_N_C);
    getXY(cx, cy, hourAngle, radius / 2, x1, y1);
    line(cx, cy, x1, y1);
    setcolor(M_N_C);
    getXY(cx, cy, minuteAngle, radius * 3 / 5, x2, y2);
    line(cx, cy, x2, y2);
    setcolor(S_N_C);
    getXY(cx, cy, secondAngle, radius * 4 / 5, x3, y3);
    line(cx, cy, x3, y3);
}

void getTime(int &hours, int &minutes, int &seconds) {
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
            hours++;
            if (hours >= 24) {
                hours = 0;
            }
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    int radius = min(centerX, centerY) - 20;
    int hours = 12, minutes = 30, seconds = 45;

    while (!kbhit()) {
        drawClockFace(centerX, centerY, radius);
        drawClock(centerX, centerY, radius, hours, minutes, seconds);
        delay(1000);
        cleardevice();
        getTime(hours, minutes, seconds);

    }

    getch();
    closegraph();
    return 0;
}

