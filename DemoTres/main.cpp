#include <winbgim.h>  // Include the WinBGIm graphics library
#include <iostream>
#include <cmath>
#include <time.h>

void fractal(int x,int y,int t){
    if(t<10){
        return;
    }
    rectangle(x,y,x+t,y+t);
    fractal(x-t/4,y-t/4,t/2);
    fractal(x+3*t/4,y+3*t/4,t/2);
    fractal(x-t/4,y+3*t/4,t/2);
    fractal(x+3*t/4,y-t/4,t/2);
}

void cuadrado(int x,int y,int t,int c){
    setfillstyle(1,c);
    bar(x-t/2,y-t/2,x+t/2,y+t/2);
}
void fractal_2(int x,int y,int t,int c){
    if(t<10){
        return;
    }
    cuadrado(x,y,t,c);
    fractal_2(x-t/2,y-t/2,t/2,c+1);
    fractal_2(x+t/2,y+t/2,t/2,c+1);
    fractal_2(x-t/2,y+t/2,t/2,c+1);
    fractal_2(x+t/2,y-t/2,t/2,c+1);
}

void fractal_3(int x,int y,int t,int c,int n){
    if(n<=0){
        return;
    }
    cuadrado(x,y,t,c);
    fractal_3(x-t/2,y-t/2,t/2,c,n-1);
    fractal_3(x+t/2,y+t/2,t/2,c,n-1);
    fractal_3(x-t/2,y+t/2,t/2,c,n-1);
    fractal_3(x+t/2,y-t/2,t/2,c,n-1);
}

int main() {
    initwindow(800,600);
    int xc=400, yc=300, r=100, start_angle=45, end_angle=45;

    srand(time(NULL));
    fractal_3(400,300,300,10,4);

    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}
