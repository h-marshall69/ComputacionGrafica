#include <graphics.h>
#include <iostream>
using namespace std;

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int tamano = 50;
    int dx = 5; // Velocidad horizontal
    int dy = 5; // Velocidad vertical

    // Colores para las letras
    int colores[] = {RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE};

    // Coordenadas iniciales de las letras "H", "I", "L", "D", "E", "B", "R", "A", "N", "D" y "T"
    int xH = 100;
    int yH = 100;
    int xI = xH + 35;
    int yI = yH;
    int xL = xI + 35;
    int yL = yI;
    int xD = xL + 20;
    int yD = yL;
    int xE = xD + 35;
    int yE = yD;
    int xB = xE + 25;
    int yB = yE;
    int xR = xB + 25;
    int yR = yB;
    int xA = xR + 35;
    int yA = yR;
    int xN = xA + 25;
    int yN = yA;
    int xD2 = xN + 25;
    int yD2 = yN;
    int xT = xD2 + 30;
    int yT = yD2;
    setlinestyle(SOLID_LINE, 0, 4);
    while (!kbhit()) {

        cleardevice();

        int colorIndex = rand() % (sizeof(colores) / sizeof(colores[0]));
        setcolor(colores[colorIndex]);
        // Letra "H"
        // Horizontal
        line(xH, yH + tamano / 2, xH + tamano / 2, yH + tamano / 2);
        // Vertical uno
        line(xH, yH, xH, yH + tamano);
        // Vertical dos
        line(xH + tamano / 2, yH, xH + tamano / 2, yH + tamano);

        // Letra "I"
        // Vertical
        line(xI + tamano / 4, yI, xI + tamano / 4, yI + tamano);
        // Horizontal uno
        line(xI, yI, xI + tamano / 2, yI);
        // Horizontal dos
        line(xI, yI + tamano, xI + tamano / 2, yI + tamano);

        // Letra "L"
        // Vertical
        line(xL, yL, xL, yL + tamano);
        // Horozontal
        line(xL, yL + tamano, xL  + tamano / 4, yL + tamano);

        // Selecciona un color aleatorio para cada letra
        colorIndex = rand() % (sizeof(colores) / sizeof(colores[0]));
        setcolor(colores[colorIndex]);
        // Letra "D"
        // Vertical uno
        line(xD, yD, xD, yD + tamano);
        // Semicírculo
        arc(xD, yD + tamano / 2, 270, 90, tamano / 2);

        // Letra "E"
        // Horizontal uno
        line(xE, yE, xE + tamano / 3, yE);
        // Vertical uno
        line(xE, yE, xE, yE + tamano);
        // Horizontal dos
        line(xE, yE + tamano / 2, xE + tamano / 3, yE + tamano / 2);
        // Horizontal tres
        line(xE, yE + tamano, xE + tamano / 3, yE + tamano);

        colorIndex = rand() % (sizeof(colores) / sizeof(colores[0]));
        setcolor(colores[colorIndex]);

        // Letra "B"
        // Vertical uno
        line(xB, yB, xB, yB + tamano);
        // Semicírculo uno
        arc(xB, yB + tamano / 4, 270, 90, tamano / 4);
        // Semicírculo dos
        arc(xB, yB + 3*(tamano / 4), 270, 90, tamano / 4);

        // Letra "R"
        // Vertical uno
        line(xR, yR, xR, yR + tamano);
        // Semicírculo
        arc(xR, yR + tamano / 4, 270, 90, tamano / 4);
        // Diagonal inversa
        line(xR, yR + tamano / 2, xR + tamano / 4, yR + tamano);

        // Letra "A"
        // Horizontal uno
        line(xA - tamano / 6, yA + tamano / 2, xA + tamano / 6, yA + tamano / 2);
        // Diagonal uno
        line(xA, yA, xA + tamano / 4, yA + tamano);
        // Diagonal dos
        line(xA, yA, xA - tamano / 4, yA + tamano);

        // Letra "N"
        // Vertical uno
        line(xN, yN, xN, yN + tamano);
        // Diagonal uno
        line(xN, yN, xN + tamano / 3, yN + tamano);
        // Diagonal dos
        line(xN + tamano / 3, yN + tamano, xN + tamano / 3, yN);

        // Selecciona un color aleatorio para cada letra
        colorIndex = rand() % (sizeof(colores) / sizeof(colores[0]));
        setcolor(colores[colorIndex]);

        // Letra "D"
        // Vertical uno
        line(xD2, yD2, xD2, yD2 + tamano);
        // Semicírculo
        arc(xD2, yD2 + tamano / 2, 270, 90, tamano / 2);

        // Letra "T"
        // Horizontal
        line(xT, yT, xT + tamano / 2, yT);
        // Vertical
        line(xT + tamano / 4, yT, xT + tamano / 4, yT + tamano);

        // Actualizamos las coordenadas de las letras para el próximo fotograma
        xH += dx;
        yH += dy;
        xI += dx;
        yI += dy;
        xL += dx;
        yL += dy;
        xD += dx;
        yD += dy;
        xE += dx;
        yE += dy;
        xB += dx;
        yB += dy;
        xR += dx;
        yR += dy;
        xA += dx;
        yA += dy;
        xN += dx;
        yN += dy;
        xD2 += dx;
        yD2 += dy;
        xT += dx;
        yT += dy;

        // Rebotamos si llegamos a los límites de la ventana
        if (xH <= 0 || (xT + tamano / 2) >= getmaxx()) {
            dx = -dx; // Cambiamos la dirección horizontal
        }
        if (yH <= 0 || yH + tamano >= getmaxy()) {
            dy = -dy; // Cambiamos la dirección vertical
        }

        delay(50); // Esperamos un poco antes de dibujar el siguiente fotograma
    }

    closegraph();

    return 0;
}
