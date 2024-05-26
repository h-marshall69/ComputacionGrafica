#include <iostream>
#include <winbgim.h>
#include <math.h>
#include <list>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
using namespace std;
class Point{
public:
    double x, y;
    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}
    Point operator+(const Point p) {
        return Point(this->x + p.x, this->y + p.y);
    }
    Point operator-(const Point p) {
        return Point(this->x - p.x, this->y - p.y);
    }
};
class Node{
public:
    Node* left;
	Node* right;
	bool nivel;
	bool root;
	int depth;
	Point pt;

	// methods
    Node(Point pt): pt(pt) {
        left = nullptr;
        right = nullptr;
    }
};
class Kdtree{
public:
    Node *root;

    // Methos
    Kdtree() {
        root = nullptr;
    }

    void add(Node *&rt, Point p, bool nivel) {
        if(!rt) {
            rt = new Node(p);
            (nivel)? rt->nivel = false : rt->nivel = true;
        }
        else {
            if(rt->nivel) {
                if(p.x < rt->pt.x) {
                    add(rt->left, p, rt->nivel);
                }
                else{
                    add(rt->right, p, rt->nivel);
                }
            }
            else{
                if(p.y < rt->pt.y) {
                    add(rt->left, p, rt->nivel);
                }
                else{
                    add(rt->right, p, rt->nivel);
                }
            }
        }

    }
    void add(double x, double y) {add(root, Point(x, y),false);}
    void draw(Node *current) {
        if(current) {
            cout << current->pt.x << ":" << current->pt.y << " ";
            line(current->pt.x, 0, current->pt.x, 600);
            draw(current->left);
            draw(current->right);
            cout << endl;
        }
    }
    void draw() {draw(root);}

};

int main() {
    initwindow(800,600);
    Kdtree k;

    k.add(400, 300);
    k.add(234, 432);
    //k.add(456, 654);
    //k.add(123, 321);
    //k.add(765, 567);
    //cout << k.root->pt.x << endl;
    k.draw();
    /*initwindow(800,600);
    while(!kbhit()){
        circle(k.root->pt.x, k.root->pt.y, 25);
        delay(16);
        cleardevice();
    }*/
    getch();
    closegraph();
    return 0;
}
