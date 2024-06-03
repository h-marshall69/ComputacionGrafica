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

void lineaM(int xini,int yini,float angulo,int largo){
    int x1,y1,x2,y2;
    x1=xini+(largo/2)*cos(angulo*M_PI/180);
    y1=yini-(largo/2)*sin(angulo*M_PI/180);
    x2=xini+(largo/2)*cos((angulo+180)*M_PI/180);
    y2=yini-(largo/2)*sin((angulo+180)*M_PI/180);
    line(x1,y1,x2,y2);
}

void lineaM2(int xini,int yini,float angulo,int largo){
    int x1,y1,x2,y2;
    x1=xini+(4*largo/6)*cos(angulo*M_PI/180);
    y1=yini-(4*largo/6)*sin(angulo*M_PI/180);
    x2=xini+(2*largo/6)*cos((angulo+180)*M_PI/180);
    y2=yini-(2*largo/6)*sin((angulo+180)*M_PI/180);
    line(x1,y1,x2,y2);
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

void loader1(int x,int y,int r,int n,float alfa,int actual,int col1,int col2){
    float angulo=360/n,angulo2=0;
    int x1,y1;
    for(int i=0;i<n;i++){
        getXY(x,y,angulo2+alfa,r,x1,y1);
        setcolor(col1);
        if(i!=actual)
        circle(x1,y1,5);
        angulo2=angulo2+angulo;
    }
    getXY(x,y,angulo*actual+alfa,r,x1,y1);
    setcolor(col2);
    circle(x1,y1,10);
}

int main() {

    initwindow(800,600);

    int actual=0;
    int alfa=5;
    while(!kbhit()){
        loader1(400,300,50,10,alfa,actual,15,10);
        delay(100);
        loader1(400,300,50,10,alfa,actual,0,0);
        actual++;
        actual=actual%10;
        alfa++;
    }

    /*Reloj r(11,59,57);
    while(!kbhit()){
        r.dibujar();
        delay(100);
        r.borrar();
        r.avanzar();
    }*/

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

    /*int angulo=0;
    while(!kbhit()){
        setcolor(15);
        circle(400,300,5);
        setcolor(10);
        lineaM2(400,300,angulo,100);
        delay(10);
        setcolor(0);
        lineaM2(400,300,angulo,100);

        angulo++;
    }*/



    getch();
    getch();
    closegraph();
    return 0;
}
