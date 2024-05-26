#include <iostream>
#include <winbgim.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int ANIMATION_DELAY = 1000; // Milisegundos de retraso entre animaciones

class DrawingFunctions {
public:
    void drawRectangleWithArc() {
        cleardevice(); // Limpiar la pantalla antes de dibujar
        setcolor(COLOR(255, 0, 0));
        rectangle(100, 150, 300, 250);
        arc(200, 150, 0, 180, 50);
        delay(ANIMATION_DELAY); // Pausa para mostrar el dibujo
    }

    void draw3DStaircase() {
        cleardevice();
        setcolor(COLOR(255, 0, 0));
        bar3d(100, 600, 400, 700, 100, 1);
        bar3d(100, 500, 350, 600, 100, 1);
        bar3d(100, 400, 300, 500, 100, 1);
        delay(ANIMATION_DELAY);
    }

    void drawRectangleWithCircles() {
        cleardevice();
        rectangle(100, 150, 300, 250);
        setcolor(COLOR(255, 255, 255));
        circle(100, 150, 30);
        circle(300, 150, 30);
        circle(300, 250, 30);
        circle(100, 250, 30);
        delay(ANIMATION_DELAY);
    }

    void drawPolygon() {
        cleardevice();
        int nums[8] = {100, 100, 200, 100, 150, 0, 100, 100};
        drawpoly(4, nums);
        delay(ANIMATION_DELAY);
    }

    void drawFilledEllipse() {
        cleardevice();
        fillellipse(200, 300, 200, 100);
        delay(ANIMATION_DELAY);
    }

    void paintUntilLine(int color) {
        cleardevice();
        setcolor(color);
        int nums[8] = {100, 100, 200, 100, 150, 0, 100, 100};
        drawpoly(4, nums);
        circle(20, 30, 10);
        circle(300, 300, 50);
        floodfill(22, 32, color);
        delay(ANIMATION_DELAY);
    }
};

int main() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    DrawingFunctions drawer;

    drawer.drawRectangleWithArc();
    drawer.draw3DStaircase();
    drawer.drawRectangleWithCircles();
    drawer.drawPolygon();
    drawer.drawFilledEllipse();
    drawer.paintUntilLine(COLOR(10, 10, 10));

    getch();
    closegraph();
    return 0;
}
