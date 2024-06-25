#include <winbgim.h>
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;
/*
void rotateZ(int cx, int cy, double angle) {
    double temp = ((x - cx)*cos(angle * M_PI / 180) - (y - cy)*sin(angle * M_PI / 180)) + cx;
    y = ((x - cx)*sin(angle * M_PI / 180) + (y - cy)*cos(angle * M_PI / 180)) + cy;
    x = temp;
}*/
void rotate(int& x1, int& y1, int angle) {
    int temp = (x * cos(angle * M_PI / 180)) - (y * sin(angle * M_PI / 180));
    y = (x * sin(angle * M_PI / 180)) + (y * cos(angle * M_PI / 180));
    x = temp;
}

void tree(int x1, int y1, int x2, int y2) {
    line(x1, y1, x2, y2);
    int dy = y2 - y1;
    if(y2 > 100) {
        tree(x1, y2, x2, y2 + dy/3);
    }
}
int main() {
    initwindow(800,600);

    srand(time(NULL));

    //tree(getmaxx()/2,getmaxy(), getmaxx()/2, getmaxy() - 100);

    int x = 400;
    int y = 400;

    //circle(x, y, 5);
    rotate(x, y, 30);
    circle(x, y, 5);
    cout<<x<<y;

    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}
