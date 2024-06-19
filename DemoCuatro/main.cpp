#include <winbgim.h>
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

void fractal_3(int x, int y, int large, int nivel) {
    if(nivel <= 0)
        return;
    line(x - large, y - large, x, y - large);
    line(x, y - large, x + large, y - large);
    line(x + large, y - large, x + large, y);
    line(x + large, y, x + large, y + large);
    line(x - large, y + large, x, y + large);
    line(x, y + large, x + large, y + large);
    line(x - large, y - large, x - large, y);
    line(x - large, y, x - large, y + large);

    fractal_3(x-large,y-large,large/2,nivel-1);
    fractal_3(x+large,y+large,large/2,nivel-1);
    fractal_3(x-large,y+large,large/2,nivel-1);
    fractal_3(x+large,y-large,large/2,nivel-1);
}

int main() {
    initwindow(800,600);

    srand(time(NULL));
    circle(getmaxx()/2, getmaxy()/2, 5);

    fractal_3(getmaxx()/2,getmaxy()/2,100, 2);


    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}
