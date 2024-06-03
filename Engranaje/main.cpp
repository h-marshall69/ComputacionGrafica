#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

void getXY(int xini, int yini, float angulo, int largo, int& x, int& y) {
    x = xini + largo * cos(angulo * M_PI / 180);
    y = yini - largo * sin(angulo * M_PI / 180);
}

void drawGear(int x, int y, int r, int n, int col1, int col2) {
    float angulo = 360.0 / n;
    float angulo2 = 0;
    int x1, y1, x2, y2, x3, y3, x4, y4;

    for (int i = 0; i < n; i++) {
        getXY(x, y, angulo2, r, x1, y1);
        getXY(x, y, angulo2 + angulo / 4, r + 20, x2, y2);
        getXY(x, y, angulo2 + 3 * angulo / 4, r + 20, x3, y3);
        getXY(x, y, angulo2 + angulo, r, x4, y4);

        setcolor(col1);
        line(x1, y1, x2, y2);
        line(x2, y2, x3, y3);
        line(x3, y3, x4, y4);

        setcolor(col2);
        line(x, y, x1, y1);
        line(x, y, x4, y4);

        angulo2 += angulo;
    }
}

int main() {
    initwindow(800, 600);

    int actual = 0;
    float alfa = 0.0;

    while (true) {
        cleardevice();
        drawGear(400, 300, 50, 6, 15, 10); // Cambiamos los parámetros para dibujar un engranaje
        delay(100);
        // Aquí podrías agregar lógica para rotar el engranaje si lo deseas
    }

    getch();
    closegraph();
    return 0;
}

