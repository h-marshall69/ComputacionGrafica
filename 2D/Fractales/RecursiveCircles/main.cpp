#include <winbgim.h>
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

void drawCircles(int x, int y, int radius) {
    circle(x, y, radius);
    if(radius > 20) {
        drawCircles(x + radius/2, y, radius/2);
        drawCircles(x - radius/2, y, radius/2);
        drawCircles(x, y + radius/2, radius/2);
        drawCircles(x, y - radius/2, radius/2);
    }
}
int main() {
    initwindow(800,600);

    srand(time(NULL));

    drawCircles(getmaxx()/2,getmaxy()/2,320);

    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}

