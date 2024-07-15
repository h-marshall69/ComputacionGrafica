#include <winbgim.h>  // Include the WinBGIm graphics library
#include <iostream>
#include <cmath>

void fractal(int x,int y,int t, int start_angle,  int end_angle){
    if(t<10){
        return;
    }
    rectangle(x,y,x+t,y+t);

    x = x + t * cos(start_angle * M_PI / 180);
    y = y - t * sin(start_angle * M_PI / 180);

    fractal(x-t/4,y-t/4,t/2, start_angle, end_angle);
    fractal(x+t/4,y-t/4,t/2, start_angle, 45);
    fractal(x-t/4,y-t/4,t/2, start_angle, 180);
    fractal(x-t/4,y-t/4,t/2, start_angle, 270);

    delay(100);
}

int main() {
    initwindow(800,600);
    int xc=400, yc=300, r=100, start_angle=0, end_angle=360;

    fractal(300,300,100, start_angle, end_angle);

    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}
