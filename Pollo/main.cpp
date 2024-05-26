#include <iostream>
#include <winbgim.h>
using namespace std;
void grafico(int x,int y,int e,int color){
    //cuerpo
    arc(x, y, 0, 270, 7*e);
    //ojo
    circle(x - 3*e, y - 2*e, 0.8*e);
    //culo
    ellipse(x,y, 270, 360, 8*e, 7*e);
    //cola
    line(x + 7*e, y, x + 8*e, y);
    //pico
    line(x - 8*e, y - e, x - 7*e, y);
    line(x - 8*e, y - e, x - 6.8*e, y - 2*e);
    //ala
    ellipse(x + 2.5*e, y + 3*e, 180, 360, 2*e, e);
    //rosa
    ellipse(x + e, y - e, 0, 360, 1.5*e, e);
    //pie izq
    line(x - 2*e, y + 6.8*e, x - 2.2*e, y + 7.5*e);
    line(x - 2.2*e, y + 7.5*e, x - 3*e, y + 7*e);
    line(x - 2.2*e, y + 7.5*e, x - 3.5*e, y + 8*e);
    line(x - 2*e, y + 7.5*e, x - 4*e, y + 7.3*e);
    //pie der
    line(x + 2*e, y + 6.8*e, x + 2.3*e, y + 7.7*e);
    line(x + 2.2*e, y + 7.5*e, x + 1.5*e, y + 7.3*e);
    line(x + 2.3*e, y + 7.5*e, x + 1.8*e, y + 8.4*e);
    line(x + 2.7*e, y + 7.5*e, x + e, y + 8*e);
}
int main()
{
    initwindow(800,800);
    int e = 20;
    /*for(int i = 0; i < 800; i += e) {
        line(0, i, 800, i);
        line(i, 0, i, 800);
    }*/
    setlinestyle(SOLID_LINE, 0, 4);
    int color, color2 = BLACK;
    while(!kbhit()) {
        setfillstyle(SOLID_FILL, YELLOW);
        bar(0, 0, 50, 50);
        setfillstyle(SOLID_FILL, BLACK);
        bar(50, 0, 100, 50);
        setfillstyle(SOLID_FILL, RED);
        bar(100, 0, 150, 50);
        setfillstyle(SOLID_FILL, BLUE);
        bar(150, 0, 200, 50);
        grafico(400,350,e,10);
        if(mousex() > 0 && mousex() < 200 && mousey() > 0 && mousey() < 50) {
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    int x;
                    int y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    color = getpixel(x, y);
                }
        }
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x;
            int y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            setfillstyle(SOLID_FILL, color);
            floodfill(x, y, WHITE);
        }
    }
    char key = getch();
    if (key == 27) {
        cout << "Se presionó Alt + F4 para cerrar la ventana." << endl;
    }

    closegraph();
    return 0;
}
