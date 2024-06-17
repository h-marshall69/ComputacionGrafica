#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define WIDTH 400
#define HEIGHT 400

using namespace std;

void drawSierpinskiCarpet(int depth, int x, int y, int size) {
    if (depth == 0) {
        bar(x, y, x + size, y + size); // Dibuja un cuadrado sólido
    } else {
        int newSize = size / 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == 1 && j == 1) {
                    // No dibujar el cuadrado central
                    setcolor(BLACK);
                    bar(x + newSize, y + newSize, x + 2 * newSize, y + 2 * newSize);
                } else {
                    drawSierpinskiCarpet(depth - 1, x + i * newSize, y + j * newSize, newSize);
                }
            }
        }
    }
}

int main() {
    //int gd = DETECT, gm;
    //initgraph(&gd, &gm, "");
    initwindow(800, 600);

    int depth = 4; // Profundidad de la alfombra de Sierpinski
    int size = min(WIDTH, HEIGHT); // Tamaño del cuadrado inicial

    setcolor(WHITE); // Color de los cuadrados
    drawSierpinskiCarpet(depth, 0, 0, size);

    while (!kbhit()) {
        delay(200);
    }

    closegraph();
    return 0;
}
