#include <winbgim.h>
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

void drawSquaresUpLeft(int x, int y, int halfSide) {
    line(x - halfSide, y - halfSide, x + halfSide, y - halfSide);
    line(x + halfSide, y - halfSide, x + halfSide, y);
    line(x - halfSide, y + halfSide, x, y + halfSide);
    line(x - halfSide, y - halfSide, x - halfSide, y + halfSide);
}

void drawSquaresUpRight(int x, int y, int halfSide) {
    line(x - halfSide, y - halfSide, x + halfSide, y - halfSide);
    line(x + halfSide, y - halfSide, x + halfSide, y + halfSide);
    line(x, y + halfSide, x + halfSide, y + halfSide);
    line(x - halfSide, y - halfSide, x - halfSide, y);
}

void drawSquaresDownLeft(int x, int y, int halfSide) {
    line(x - halfSide, y - halfSide, x, y - halfSide);
    line(x + halfSide, y, x + halfSide, y + halfSide);
    line(x - halfSide, y + halfSide, x + halfSide, y + halfSide);
    line(x - halfSide, y - halfSide, x - halfSide, y + halfSide);
}

void drawSquaresDownRight(int x, int y, int halfSide) {
    line(x, y - halfSide, x + halfSide, y - halfSide);
    line(x + halfSide, y - halfSide, x + halfSide, y + halfSide);
    line(x - halfSide, y + halfSide, x + halfSide, y + halfSide);
    line(x - halfSide, y, x - halfSide, y + halfSide);
}

void drawSquares(int x, int y, int sideLength, int depth) {
    if(depth > 0) {
        drawSquares(x - sideLength, y - sideLength, sideLength/2, depth-1);
        drawSquares(x + sideLength, y - sideLength, sideLength/2, depth-1);
        drawSquares(x - sideLength, y + sideLength, sideLength/2, depth-1);
        drawSquares(x + sideLength, y + sideLength, sideLength/2, depth-1);


        rectangle(x - sideLength, y - sideLength, x + sideLength, y + sideLength);
        setcolor(BLACK);
        floodfill(x, y, WHITE);
        setcolor(WHITE);
    }
}


int main() {
    initwindow(800,600);

    srand(time(NULL));
    //circle(getmaxx()/2, getmaxy()/2, 5);

    //fractal_3(getmaxx()/2,getmaxy()/2,100, 2);
    drawSquares(getmaxx()/2,getmaxy()/2,100, 4);


    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}
