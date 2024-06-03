#include <winbgim.h>
#include <iostream>
#include <math.h>

using namespace std;

void linea(int xini,int yini,float angulo,int largo){
    int x,y;
    x=xini+largo*cos(angulo*M_PI/180);
    y=yini-largo*sin(angulo*M_PI/180);
    line(xini,yini,x,y);
}

void getXY(int xini,int yini,float angulo,int largo,int&x,int&y){
    x=xini+largo*cos(angulo*M_PI/180);
    y=yini-largo*sin(angulo*M_PI/180);
}

class Reloj{
    private:
        int h;
        int m;
        int s;

        int x;
        int y;
        int r;
    public:
        Reloj(int H,int M,int S){
            h=H;
            m=M;
            s=S;
            x=400;
            y=300;
            r=100;
        }
        void setHora(int H){
            h=H;
        }
        void dibujar(){
            setcolor(15);
            circle(x,y,r);
            setcolor(4);
            linea(x,y,90+(12-h)*30,4*r/6);
            setcolor(10);
            linea(x,y,90+(60-m)*6,5*r/6);
            setcolor(14);
            linea(x,y,90+(60-s)*6,5*r/6);
        }
        void borrar(){
            setcolor(0);
            circle(x,y,r);
            linea(x,y,90+(12-h)*30,4*r/6);
            linea(x,y,90+(60-m)*6,5*r/6);
            linea(x,y,90+(60-s)*6,5*r/6);
        }
        void avanzar(){
            s++;
            if(s==60){
                s=0;
                m++;
            }
            if(m==60){
                h++;
                m=0;
            }
        }
};

int main() {

    initwindow(800,600);

    Reloj r(11,59,57);

    while(!kbhit()){
        r.dibujar();
        delay(100);
        r.borrar();
        r.avanzar();
    }

    /*int x,y;
    float angulo=0;
    while(!kbhit()){
        getXY(400,300,angulo+=2,150,x,y);
        setcolor(10);
        circle(x,y,5);
        delay(10);
        setcolor(0);
        circle(x,y,5);
    }*/

    getch();
    getch();
    closegraph();
    return 0;
}
