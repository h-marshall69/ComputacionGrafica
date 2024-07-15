#include <iostream>
#include <winbgim.h>
#include <math.h>
using namespace std;


void getXY(int xini, int yini, float angulo, int largo, int& x, int& y) {
    x = xini + largo * cos(angulo * M_PI / 180);
    y = yini - largo * sin(angulo * M_PI / 180);
}
void pollito(int x,int y, int e){
    setcolor(8);
    setlinestyle(0,0,4);
    arc(x+8*e,y+7*e,0,270,e*7);
    ellipse(x+8*e,y+7*e,270,360,e*9,e*7);
    circle(x+5*e,y+5*e,e*0.75);
    ellipse(x+10.8125*e,y+10*e,180,350,e*2.25,e*1.5);
    setlinestyle(0,0,1);
    ellipse(x+9*e,y+6*e,0,360,e*1.5,e*1);
    setlinestyle(0,0,4);
    int x1, y1;
    int x2, y2;

    //PATA1
    getXY(x+8*e,y+7*e,255,7*e,x1,y1);
    getXY(x+8*e,y+7*e,252,8*e,x2,y2);
    line(x1,y1,x2,y2);
    getXY(x+8*e,y+7*e,252,8*e,x1,y1);
    getXY(x+8*e,y+7*e,257,8.2*e,x2,y2);
    line(x1,y1,x2,y2);
    getXY(x+8*e,y+7*e,252,8*e,x1,y1);
    getXY(x+8*e,y+7*e,245,7.6*e,x2,y2);
    line(x1,y1,x2,y2);
    getXY(x+8*e,y+7*e,252,8*e,x1,y1);
    getXY(x+8*e,y+7*e,241,8.2*e,x2,y2);
    line(x1,y1,x2,y2);
    getXY(x+8*e,y+7*e,252,8*e,x1,y1);
    getXY(x+8*e,y+7*e,250,8.8*e,x2,y2);
    line(x1,y1,x2,y2);
    //PATA2
    getXY(x+8*e,y+7*e,288,7.1*e,x1,y1);
    getXY(x+8*e,y+7*e,290,8.2*e,x2,y2);
    line(x1,y1,x2,y2);
    getXY(x+8*e,y+7*e,290,8.2*e,x1,y1);
    getXY(x+8*e,y+7*e,282,7.8*e,x2,y2);
    line(x1,y1,x2,y2);
    getXY(x+8*e,y+7*e,290,8.2*e,x1,y1);
    getXY(x+8*e,y+7*e,278,8.4*e,x2,y2);
    line(x1,y1,x2,y2);
    getXY(x+8*e,y+7*e,290,8.2*e,x1,y1);
    getXY(x+8*e,y+7*e,284,9*e,x2,y2);
    line(x1,y1,x2,y2);
    getXY(x+8*e,y+7*e,290,8.2*e,x1,y1);
    getXY(x+8*e,y+7*e,294,8.2*e,x2,y2);
    line(x1,y1,x2,y2);

    getXY(x+8*e,y+7*e,360,7*e,x1,y1);
    getXY(x+8*e,y+7*e,360,9 *e,x2,y2);
    line(x1,y1,x2,y2);
    getXY(x+8*e,y+7*e,180,7*e,x1,y1);
    getXY(x+8*e,y+7*e,172,8 *e,x2,y2);
    line(x1,y1,x2,y2);
    getXY(x+8*e,y+7*e,172,8*e,x1,y1);
    getXY(x+8*e,y+7*e,160,7 *e,x2,y2);
    line(x1,y1,x2,y2);
    setfillstyle(SOLID_FILL,14);
    floodfill(x+8*e,y+2*e,8);
    floodfill(x+0.5*e,y+5.75*e,8);
    setfillstyle(SOLID_FILL,0);
    floodfill(x+5*e,y+5*e,8);
    setfillstyle(SOLID_FILL,12);
    floodfill(x+9*e,y+6*e,8);
}
int main()
{
    initwindow(800,800);
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    while(!kbhit()) {
        pollito(centerX - 150, centerY - 150, 20);
        //delay(100);
        //cleardevice();
    }
    getch();
    closegraph();
    return 0;
}
