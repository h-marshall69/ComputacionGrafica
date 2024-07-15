#include <cmath>
#include <iostream>
#include <graphics.h>

class sierpinski_curve {
public:
    void draw(int size, int length, int order);
private:
    static std::string rewrite(const std::string& s);
    void line();
    void execute(const std::string& s);
    double x_;
    double y_;
    int angle_;
    int length_;
};

void sierpinski_curve::draw(int size, int length, int order) {
    length_ = length;
    x_ = length / std::sqrt(2.0);
    y_ = 2 * x_;
    angle_ = 45;

    std::string s = "F--XF--F--XF";
    for (int i = 0; i < order; ++i)
        s = rewrite(s);
    execute(s);
}

std::string sierpinski_curve::rewrite(const std::string& s) {
    std::string t;
    for (char c : s) {
        if (c == 'X')
            t += "XF+G+XF--F--XF+G+X";
        else
            t += c;
    }
    return t;
}

void sierpinski_curve::line() {
    double theta = (3.14159265359 * angle_) / 180.0;
    double new_x = x_ + length_ * std::cos(theta);
    double new_y = y_ - length_ * std::sin(theta);
    line(int(x_), int(y_), int(new_x), int(new_y));
    x_ = new_x;
    y_ = new_y;
}

void sierpinski_curve::execute(const std::string& s) {
    moveto(int(x_), int(y_));
    for (char c : s) {
        switch (c) {
        case 'F':
        case 'G':
            line();
            break;
        case '+':
            angle_ = (angle_ + 45) % 360;
            break;
        case '-':
            angle_ = (angle_ - 45) % 360;
            break;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    sierpinski_curve s;
    s.draw(545, 7, 5);

    getch();
    closegraph();
    return 0;
}
