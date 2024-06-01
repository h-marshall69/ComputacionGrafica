#include <iostream>
#include <winbgim.h>
#include <math.h>
using namespace std;
void linea(int xini, int yini, float angulo, int largo) {
    int x, y;
    x = largo*cos(angulo*M_PI/180) + xini;
    y = largo*sin(angulo*M_PI/180) + yini;
    line(xini, yini, x, y);
}

void getXY(int xini, int yini, float angulo, int largo, int &x, int &y) {
    x = largo*cos(angulo*M_PI/180) + xini;
    y = largo*sin(angulo*M_PI/180) + yini;
}
class Pacman{
    private:
        int x;
        int y;
        int e;
        float angulo;
        int inc;
        int incX;
        int incY;
    public:
        Pacman(int X,int Y,int E,float A,int INC){
            x=X;
            y=Y;
            e=E;
            angulo=A;
            inc=INC;
            incX=1;
            incY=1;
        }
        void abrirCerrarBoca(){
            angulo+=inc;
            if(angulo<0 || angulo>45)
                inc=-inc;
        }
        void mover(){
            x+=incX;
            y+=incY;
            if(x<0 || x>getmaxx()-6*e){
                incX =- incX;
            }
            if(y<0 || y>getmaxy()-6*e)
                incY = -incY;
        }
        void graficar(int color){
            setcolor(color);
            arc(x+3*e,y+3*e,angulo,360-angulo,3*e);
            linea(x+3*e,y+3*e,angulo,3*e);
            linea(x+3*e,y+3*e,360-angulo,3*e);
        }
};

int main() {

    initwindow(800,600);

    Pacman a(100,400,15,10,1);
    Pacman b(200,300,20,5,-1);
    Pacman c(100,200,10,10,1);
    Pacman d(600,300,25,25,-1);

    while(!kbhit()){
        a.graficar(10);
        b.graficar(15);
        c.graficar(7);
        d.graficar(14);

        delay(10);

        a.graficar(0);
        b.graficar(0);
        c.graficar(0);
        d.graficar(0);

        a.abrirCerrarBoca();
        b.abrirCerrarBoca();
        c.abrirCerrarBoca();
        d.abrirCerrarBoca();

        a.mover();
        b.mover();
        c.mover();
        d.mover();
    }

    getch();
    getch();
    closegraph();
    return 0;
}
