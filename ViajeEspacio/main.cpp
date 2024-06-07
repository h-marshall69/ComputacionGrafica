#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const int NUM_STARS = 100;
const float SPEED = 10.0;

struct Star {
    float x, y;
    float z;
};

void initializeStars(Star stars[], int numStars) {
    for (int i = 0; i < numStars; ++i) {
        stars[i].x = (rand() % WIDTH) - WIDTH / 2;
        stars[i].y = (rand() % HEIGHT) - HEIGHT / 2;
        stars[i].z = rand() % WIDTH;
    }
}

void updateStars(Star stars[], int numStars, float speed) {
    for (int i = 0; i < numStars; ++i) {
        stars[i].z -= speed;
        if (stars[i].z < 1) {
            stars[i].x = (rand() % WIDTH) - WIDTH / 2;
            stars[i].y = (rand() % HEIGHT) - HEIGHT / 2;
            stars[i].z = WIDTH;
        }
    }
}

void drawStars(Star stars[], int numStars) {
    for (int i = 0; i < numStars; ++i) {
        float sx = stars[i].x / stars[i].z * WIDTH + WIDTH / 2;
        float sy = stars[i].y / stars[i].z * HEIGHT + HEIGHT / 2;
        float brightness = 1 - stars[i].z / WIDTH;
        int color = 15 * brightness;
        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        fillellipse(sx, sy, 4, 4);
    }
}

int main() {
    initwindow(WIDTH, HEIGHT, "Space");

    Star stars[NUM_STARS];
    initializeStars(stars, NUM_STARS);

    while (true) {
        cleardevice();

        updateStars(stars, NUM_STARS, SPEED);
        drawStars(stars, NUM_STARS);

        delay(10);

        if (kbhit()) {
            if (getch() == 27) break; // Escape key to exit
        }
    }

    closegraph();
    return 0;
}
