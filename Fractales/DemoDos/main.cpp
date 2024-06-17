#include <winbgim.h>  // Include the WinBGIm graphics library
#include <iostream>
#include <cmath>

void fractal(int x,int y,int t){
    if(t<10){
        return;
    }
    rectangle(x,y,x+t,y+t);
    fractal(x-t/4,y-t/4,t/2);
    fractal(x+3*t/4,y+3*t/4,t/2);
    fractal(x-t/4,y+3*t/4,t/2);
    fractal(x+3*t/4,y-t/4,t/2);
    //delay(100);
}


void cuadrado(int x,int y,int t){
    setfillstyle(1, t%11);
    bar(x-t/2,y-t/2,x+t/2,y+t/2);
}
void fractal_2(int x,int y,int t){
    if(t<10){
        return;
    }


    fractal_2(x-t/2,y-t/2,t/2);
    fractal_2(x+t/2,y+t/2,t/2);
    fractal_2(x-t/2,y+t/2,t/2);
    fractal_2(x+t/2,y-t/2,t/2);
    cuadrado(x,y,t);
}

int main() {
    initwindow(800,600);
    int xc=400, yc=300, r=100, start_angle=45, end_angle=45;

    fractal_2(400,300,150);

    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}
