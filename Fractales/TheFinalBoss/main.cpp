#include <winbgim.h>
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

void drawSquares(int x1, int y1, int x2, int y2, int n) {
    if(n > 0) {
        //int dx = x2 - x1;
        //int dy = y2 - y1;
        line(x1, y2, x2, y2);
        line(x2, y1 + 100, x2, y2);
        //line(x1 - dx, y1)
        drawSquares(x1 + y2/3, y2 + y2/3, x2 + y2/3, y2 + y2/3, n - 1);
        drawSquares(x1 + y2/3, y2 + y2/3, x2 + y2/3, y2 + y2/3, n - 1);
    }

}

void fractal(int x, int y, int t, int n) {
    if(n > 0) {
        int dx1 = x - t;
        int dy1 = y - t;
        int dx2 = x + t;
        int dy2 = y - t;
        int dx3 = x + t;
        int dy3 = y + t;
        int dx4 = x - t;
        int dy4 = y + t;
        //line(dx);
        //rectangle(x, y, dx, dy);
        circle(dx1, dy1, 5);
        circle(dx2, dy2, 5);
        circle(dx3, dy3, 5);
        circle(dx4, dy4, 5);
        //line(x - t*n, y - t, x, y - t);
        //line(x + t, y + t, x, y + t);
        //line(x, y - t, x, y);
        //line(x + t, y, x, y);
        //line(x, y + t, x, y);
        fractal(x, y, t + 50, n - 1);
        //fractal(x - t, y + t, t/n, n - 1);
        //fractal(x + t, y - t, t/n, n - 1);
        //fractal(x - t, y - t, t/n, n - 1);
    }
}
int main() {
    initwindow(800,600);

    srand(time(NULL));
    //circle(getmaxx()/2, getmaxy()/2, 5);

    fractal(getmaxx()/2,getmaxy()/2,100, 4);
    //drawSquares(400, 300, 500, 300, 4);


    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}
