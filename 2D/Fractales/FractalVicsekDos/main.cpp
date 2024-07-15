#include <iostream>
#include <winbgim.h>
#include <math.h>
using namespace std;

void nothing(int x, int y, int l, int n) {
    if (n == 0) {
        line(x - l/3, y, x + l/3, y);
        line(x, y - l/3, x, y + l/3);
    } else {
        nothing(x + l / 3, y, l / 3, n - 1);
        nothing(x + l / 3, y + l / 3, l / 3, n - 1);
        nothing(x + l / 3, y + 2 * l / 3, l / 3, n - 1);
        nothing(x, y + l / 3, l / 3, n - 1);
        nothing(x + 2 * l / 3, y + l / 3, l / 3, n - 1);
    }
}

int main() {
    initwindow(800, 600);

    int l = 550;
    int depth = 3;

    nothing((getmaxx() - l)/2, (getmaxy() - l)/2, l, depth);

    getch();
    closegraph();
    return 0;
}
