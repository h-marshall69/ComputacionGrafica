#include <graphics.h>
#include <iostream>
#include <cmath>
#include <conio.h>
using namespace std;

class Point2D {
public:
    double x;
    double y;
    Point2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

class Polar {
public:
    Point2D center;
    double scalar;
    Polar(double x = 0.0, double y = 0.0, double scalar = 1.0) : center(Point2D(x, y)), scalar(scalar) {}
    explicit Polar(Point2D center, double scalar = 1.0) : center(center), scalar(scalar){}
    void rotate(double angle, int &x, int &y, int large) {
        double radian = angle * M_PI / 180.0;
        x = center.x + static_cast<int>((large * cos(radian)));
        y = center.y - static_cast<int>((large * sin(radian)));
    }
    void setScalar(double scalar) {
        if (scalar > 1) {
            this->scalar = scalar;
        }
    }

    void draw(int angle) {
        int x;
        int y;
        int x1;
        int y1;
        setlinestyle(0,0,3);
        //frente
        rotate(90.0 + angle, x, y, 5.6 * scalar);
        arc(x, y, 180 + angle, 360 + angle, scalar);

        //osico
        rotate(270.0 + angle, x, y, 4 * scalar);
        circle(x, y, 1.5 * scalar);

        rotate(300.0 + angle, x, y, 5.5 * scalar);
        rotate(45.0 + angle, x1, y1, 2 * scalar);
        line(x, y, x1, y1);

        rotate(240.0 + angle, x, y, 5.5 * scalar);
        rotate(135.0 + angle, x1, y1, 2 * scalar);
        line(x, y, x1, y1);

        rotate(270.0 + angle, x, y, 5.5 * scalar);
        rotate(270.0 + angle, x1, y1, 6.3 * scalar);
        line(x, y, x1, y1);

        rotate(255.0 + angle, x, y, 6.5 * scalar);
        rotate(285.0 + angle, x1, y1, 6.5 * scalar);
        line(x, y, x1, y1);

        rotate(255.0 + angle, x, y, 6.5 * scalar);
        rotate(245.0 + angle, x1, y1, 6.5 * scalar);
        line(x, y, x1, y1);

        rotate(285.0 + angle, x, y, 6.5 * scalar);
        rotate(295.0 + angle, x1, y1, 6.5 * scalar);
        line(x, y, x1, y1);

        rotate(260.0 + angle, x, y, 4 * scalar);
        circle(x, y, 0.3 * scalar);
        rotate(280.0 + angle, x, y, 4 * scalar);
        circle(x, y, 0.3* scalar);

        //Ojo derecho
        rotate(25.0 + angle, x, y, 5 * scalar);
        circle(x, y, scalar);

        //Ojo izquierdo
        rotate(155.0 + angle, x, y, 5 * scalar);
        circle(x, y, scalar);


        /**  segmento de cara derecho  **/
        rotate(0.0 + angle, x, y, 3 * scalar);
        arc(x, y, 0 + angle, 110 + angle, 6 * scalar);

        //oreja derecha
        rotate(35.0 + angle, x, y, 8 * scalar);
        arc(x, y, 311 + angle, 153 + angle, 3 * scalar);
        arc(x, y, 318 + angle, 146 + angle, 2 * scalar);

        /**  segmento de cara izquierdo  **/
        rotate(180.0 + angle, x, y, 3 * scalar);
        arc(x, y, 70 + angle, 180 + angle, 6 * scalar);
        //oreja izquierdo
        rotate(145.0 + angle, x, y, 8 * scalar);
        arc(x, y, 27 + angle, 229 + angle, 3 * scalar);
        arc(x, y, 34 + angle, 222 + angle, 2 * scalar);

        //barbilla:
        rotate(260.0 + angle, x, y, 8 * scalar);
        rotate(280.0 + angle, x1, y1, 8 * scalar);
        line(x, y, x1, y1);

        rotate(300.0 + angle, x, y, 8 * scalar);
        rotate(280.0 + angle, x1, y1, 8 * scalar);
        line(x, y, x1, y1);

        rotate(300.0 + angle, x, y, 8 * scalar);
        rotate(0.0 + angle, x1, y1, 9 * scalar);
        line(x, y, x1, y1);



        rotate(260.0 + angle, x, y, 8 * scalar);
        rotate(240.0 + angle, x1, y1, 8 * scalar);
        line(x, y, x1, y1);

        rotate(180.0 + angle, x, y, 9 * scalar);
        rotate(240.0 + angle, x1, y1, 8 * scalar);
        line(x, y, x1, y1);

        rotate(270.0 + angle, x, y, 10 * scalar);
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    Polar polar(centerX, centerY, 20);
    int angle = 0;
    while (true) {
        cleardevice();

        outtextxy(getmaxx() - 120, getmaxy() - 70, "Polar...");
        outtextxy(getmaxx() - 120, getmaxy() - 50, "Rotation : A or B");
        outtextxy(getmaxx() - 120, getmaxy() - 30, "Scalar : Q or E");

        if (kbhit()) {
            char key = getch();
            if (key == 'q' || key == 'Q') {
                polar.setScalar(polar.scalar + 0.5);
            } else if (key == 'e' || key == 'E') {
                polar.setScalar(polar.scalar - 0.5);
            }else if (key == 'a' || key == 'A') {
                angle++;
            }else if (key == 'd' || key == 'D') {
                angle--;
            } else {
                closegraph();
            }
        }

        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(x > getmaxx() /2) {
                polar.center.x += 20;
            } else {
                polar.center.x -= 20;
            }
            if(y > getmaxy() /2) {
                polar.center.y += 20;
            } else {
                polar.center.y -= 20;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }

        polar.draw(angle);
        delay(16);
    }

    return 0;
}
