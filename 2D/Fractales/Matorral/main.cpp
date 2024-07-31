#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

void getXY(int xini, int yini, float angulo, int largo, int& x, int& y) {
    x = xini + largo * sin(angulo * M_PI / 180);
    y = yini - largo * cos(angulo * M_PI / 180);
}

void Arbol2(int x, int y, int l, double angulo, int n) {
    int x2;
    int y2;
    getXY(x, y, angulo, l, x2, y2);
    line(x, y, x2, y2);

    if(n > 0) {
        Arbol2(x2, y2, l * 2 / 3, angulo + 20, n - 1); // 聲gulo m嫳 peque隳 a la izquierda
        Arbol2(x2, y2, l * 2 / 3, angulo + 30, n - 1); // 聲gulo m嫳 grande a la derecha
    }
}

void Arbol22(int x1, int y1, int x2, int y2, int depth) {
    if (depth == 0) {
        line(x1, y1, x2, y2);
    } else {
        int dx = x2 - x1;
        int dy = y2 - y1;
        int x3 = x1 + dx / 3;
        int y3 = y1 + dy / 3;
        int x5 = x1 + 2 * dx / 3;
        int y5 = y1 + 2 * dy / 3;

        int x4 = x3 + (x5 - x3) * cos(M_PI / 3) - (y5 - y3) * sin(M_PI / 3);
        int y4 = y3 + (x5 - x3) * sin(M_PI / 3) + (y5 - y3) * cos(M_PI / 3);

    }
}

void Rama(int x, int y, int large, int depth, int branch_angle) {
        // Coordenadas de la primera rama
        int x4 = x + large * cos(branch_angle * M_PI / 180);
        int y4 = y - large * sin(branch_angle * M_PI / 180);
        int x5 = x4 + large * cos((branch_angle - 20) * M_PI / 180);
        int y5 = y4 - large * sin((branch_angle - 20) * M_PI / 180);
        int x6 = x5 + large * cos((branch_angle - 40) * M_PI / 180);
        int y6 = y5 - large * sin((branch_angle - 40) * M_PI / 180);

        // Coordenadas de la segunda rama
        int x7 = x + large * cos((branch_angle + 50) * M_PI / 180);
        int y7 = y - large * sin((branch_angle + 50) * M_PI / 180);
        int x8 = x7 + large * cos((branch_angle + 30) * M_PI / 180);
        int y8 = y7 - large * sin((branch_angle + 30) * M_PI / 180);
        int x9 = x8 + large * cos(branch_angle * M_PI / 180);
        int y9 = y8 - large * sin(branch_angle * M_PI / 180);

        // Dibujo de la primera rama
        line(x, y, x4, y4);
        line(x4, y4, x5, y5);
        line(x5, y5, x6, y6);

        // Dibujo de la segunda rama
        line(x, y, x7, y7);
        line(x7, y7, x8, y8);
        line(x8, y8, x9, y9);

    if(depth > 0) {
        int d = 0;
        Rama(x, y, large/2, depth - 1, branch_angle - d);
        Rama(x4, y4, large/2, depth - 1, branch_angle - d);
        Rama(x5, y5, large/2, depth - 1, branch_angle - d);
        Rama(x7, y7, large/2, depth - 1, branch_angle - d);
        Rama(x8, y8, large/2, depth - 1, branch_angle - d);
        Rama(x9, y9, large/2, depth - 1, branch_angle - d);
    }
}

void Arbol(int x, int y, int large, int depth, double angle, double branch_angle) {
    // Coordenadas del tronco principal
    int x1 = x;
    int y1 = y;

    int x2 = x1;
    int y2 = y1 - large;

    if(depth > 0) {
        Rama(x2, y2, large, depth, branch_angle);
    }

    int x3 = x2;
    int y3 = y2 - large;

    // Dibuja el tronco principal
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);

    // Dibujo de la ramas
    Rama(x3, y3, large, depth, branch_angle);

}

int main() {
    initwindow(800, 600);

    int startX = getmaxx() / 2;
    int startY = getmaxy();
    int large = 100;
    double angle = -90; // 聲gulo inicial (vertical hacia arriba)
    int depth = 3; // Profundidad del 嫫bol fractal
    double branch_angle = 70; // 聲gulo de las ramas

    Arbol(startX, startY, large, depth, angle, branch_angle);

    getch();
    closegraph();
    return 0;
}

/* Coordenadas de la primera rama
    int x4 = x3 + large * cos(75 * M_PI / 180);
    int y4 = y3 - large * sin(75 * M_PI / 180);
    int x5 = x4 + large * cos(60 * M_PI / 180);
    int y5 = y4 - large * sin(60 * M_PI / 180);
    int x6 = x5 + large * cos(50 * M_PI / 180);
    int y6 = y5 - large * sin(50 * M_PI / 180);

    // Coordenadas de la segunda rama
    int x7 = x3 - large * cos(60 * M_PI / 180);
    int y7 = y3 - large * sin(60 * M_PI / 180);
    int x8 = x7 - large * cos(80 * M_PI / 180);
    int y8 = y7 - large * sin(80 * M_PI / 180);
    int x9 = x8 - large * cos(110 * M_PI / 180);
    int y9 = y8 - large * sin(110 * M_PI / 180);*/


     /* Dibujo de la primera rama
    line(x3, y3, x4, y4);
    line(x4, y4, x5, y5);
    line(x5, y5, x6, y6);

    // Dibujo de la segunda rama
    line(x3, y3, x7, y7);
    line(x7, y7, x8, y8);
    line(x8, y8, x9, y9);*/
