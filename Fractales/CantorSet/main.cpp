#include <winbgim.h>
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

void cantor(int x, int y, int length) {
    line(x - length, y, x + length, y);
    if(length > 0) {
        cantor(x - length + length/3, y + 30,length/3);
        cantor(x + length - length/3, y + 30,length/3);
    }
}
int main() {
    initwindow(800,600);

    srand(time(NULL));

    cantor(getmaxx()/2,getmaxy()/3,320);

    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}
