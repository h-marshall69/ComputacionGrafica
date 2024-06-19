#include <winbgim.h>
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

void drawLine(int x1, int y1, int x2, int y2) {
    line(x1, y1, x2, y2);
    int dx = x2 - x1;
    int dy = y2 - y1;
    if(dy == 0 && dx > 4) {
        drawLine(x1, y1 - dx/3, x1, y1 + dx/3);
        drawLine(x2, y1 - dx/3, x2, y1 + dx/3);
    } else if(dx == 0 && dy > 4) {
        drawLine(x1 - dy/3, y1, x1 + dy/3, y1);
        drawLine(x1 - dy/3, y2, x1 + dy/3, y2);
    }
}
int main() {
    initwindow(800,600);

    srand(time(NULL));

    drawLine(getmaxx()/2 - 150,getmaxy()/2, getmaxx()/2 + 150, getmaxy()/2);

    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}
