#include <winbgim.h>  // Include the WinBGIm graphics library
#include <iostream>
#include <cmath>
#include <time.h>

void getXY(int xo, int yo, float alfa, int r, int&x, int&y){
    x = xo+r*cos(alfa*M_PI/180);
    y = yo-r*sin(alfa*M_PI/180);
}
void triangulo(int x,int y,int t){
    int x1,y1,x2,y2;
    getXY(x,y,240,t,x1,y1);
    getXY(x,y,300,t,x2,y2);
    moveto(x,y);
    lineto(x1,y1);
    lineto(x2,y2);
    lineto(x,y);
}

void TrianguloSierpinski(int x,int y,int t,int nivel){
    if(nivel==10){
        return;
    }
    setcolor(10);
    triangulo(x,y,t);

    TrianguloSierpinski(x,y,t/2,nivel+1);
    int x1,y1;
    getXY(x,y,240,t/2,x1,y1);
    TrianguloSierpinski(x1,y1,t/2,nivel+1);
    getXY(x,y,300,t/2,x1,y1);
    TrianguloSierpinski(x1,y1,t/2,nivel+1);
}

void cuadrado(int x,int y,int t,int fondo){
    setfillstyle(1,fondo);
    bar(x,y,x+t/3,y+t/3);
    //bar(x+t/3,y,t/3,nivel-1);
    //bar(x+2*t/3,y,t/3,nivel-1);

    //bar(x,y+t/3,t/3,nivel-1);
    bar(x+t/3,y+t/3,x+2*t/3,y+2*t/3);
    //bar(x+2*t/3,y+t/3,t/3,nivel-1);

    //bar(x,y+2*t/3,t/3,nivel-1);
    //bar(x+t/3,y+2*t/3,t/3,nivel-1);
    bar(x+2*t/3,y+2*t/3,x+t,y+t);
}

void AlfombraSierpinski(int x,int y,int t,int nivel){
    if(nivel==0)
        return;
    //setfillstyle(1,14);

    bar(x,y,x+t,y+t);
    setcolor(BLACK);
    rectangle(x,y,x+t,y+t);
    AlfombraSierpinski(x,y,t/3,nivel-1);
    AlfombraSierpinski(x+t/3,y,t/3,nivel-1);
    AlfombraSierpinski(x+2*t/3,y,t/3,nivel-1);

    AlfombraSierpinski(x,y+t/3,t/3,nivel-1);
    //AlfombraSierpinski(x+t/3,y+t/3,t/3,nivel-1);
    AlfombraSierpinski(x+2*t/3,y+t/3,t/3,nivel-1);

    AlfombraSierpinski(x,y+2*t/3,t/3,nivel-1);
    AlfombraSierpinski(x+t/3,y+2*t/3,t/3,nivel-1);
    AlfombraSierpinski(x+2*t/3,y+2*t/3,t/3,nivel-1);
}

int main() {
    initwindow(800,600);

    //cuadrado(250,10,450,10);
    AlfombraSierpinski(10, 10, 500, 5);

    getch();  // Wait for a key press
    closegraph();  // Close the graphics mode

    return 0;
}
