#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

void nose(int x, int y, int x1, int y1) {
    line(x, y, x1, y1);
    nose(x, y, x1, y1);
}

int main() {
    initwindow(800,600);

    int depth = 4;
    int x = 100, y = 300;
    int x1 = 700, y1 = 300;

    nose(x, y, x1, y1);

    while (!kbhit()) {
        delay(200);
    }

    closegraph();
    return 0;
}
