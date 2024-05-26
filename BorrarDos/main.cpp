#include <iostream>
#include <winbgim.h>
#include <math.h>
#include <list>
#include <vector>
using namespace std;

class Point {
public:
    double x, y;
    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}
};

class Particle {
public:
    Point position;
    Point velocity;
    int radio;
    Particle(double x, double y, double vx, double vy): position(x, y), velocity(vx, vy) {
        radio = 20;
    }

    void update() {
        position.x += velocity.x;
        position.y += velocity.y;

        if (position.x - radio < 0 || position.x + radio > 800)
            velocity.x = -velocity.x;
        if (position.y - radio < 0 || position.y + radio > 600)
            velocity.y = -velocity.y;
    }
    bool operator==(const Particle& other) const {
        return position.x == other.position.x && position.y == other.position.y && radio == other.radio;
    }
    /*void update(int minx = 0, int miny = 0, int maxx = 800, int maxy = 600) {
        position.x += velocity.x;
        position.y += velocity.y;

        if (position.x - radio < minx || position.x + radio > maxx)
            velocity.x = -velocity.x;
        if (position.y - radio < miny || position.y + radio > maxy)
            velocity.y = -velocity.y;
    }*/

    void draw() {
        circle(position.x, position.y, radio);
    }



};

class KDNode {
public:
    Point point;
    KDNode* left;
    KDNode* right;
    vector<Particle*> positionsLeft;
    vector<Particle*> positionsRight;
    KDNode(Point pt) : point(pt), left(nullptr), right(nullptr) {}
};

class KDTree {
private:
    KDNode* root;
    list<Particle> &pc;


    void collisions(vector<Particle*>& particles) {
        for (auto it1 = particles.begin(); it1 != particles.end(); ++it1) {
            auto it2 = it1;
            ++it2;
            for (; it2 != particles.end(); ++it2) {
                double dx = (*it1)->position.x - (*it2)->position.x;
                double dy = (*it1)->position.y - (*it2)->position.y;
                double distance = sqrt(dx * dx + dy * dy);

                if (distance < 40) { // Collision radius
                    (*it1)->velocity.x = -(*it1)->velocity.x;
                    (*it1)->velocity.y = -(*it1)->velocity.y;
                    (*it2)->velocity.x = -(*it2)->velocity.x;
                    (*it2)->velocity.y = -(*it2)->velocity.y;
                    pc.push_front(Particle(300, 400, -1.0, -1.0));
                }
            }
        }
    }
    void insertRec(KDNode *&root, Point point, int depth) {
        if(root == nullptr) {
            root = new KDNode(point);
        } else {
            int cd = depth % 2;
            if(cd == 0) {
                if(point.x < root->point.x) {
                    insertRec(root->left, point, depth + 1);
                }
                else
                    insertRec(root->right, point, depth + 1);
            } else {
                if(point.y < root->point.y)
                    insertRec(root->left, point, depth + 1);
                else
                    insertRec(root->right, point, depth + 1);
            }
        }
    }
    void addParticle(KDNode * rt, Particle &particle, int depth) {
        if(rt) {
            int cd = depth % 2;
            if(cd == 0) {
                if(particle.position.x < rt->point.x) {
                    if(rt->left) {
                        addParticle(rt->left, particle, depth + 1);
                    } else {
                        rt->positionsLeft.push_back(&particle);
                    }
                } else {
                    if(rt->right) {
                        addParticle(rt->right, particle, depth + 1);
                    } else {
                        rt->positionsRight.push_back(&particle);
                    }
                }
            } else {
                if(particle.position.y < rt->point.y) {
                    if(rt->left) {
                        addParticle(rt->left, particle, depth + 1);
                    } else {
                        rt->positionsLeft.push_back(&particle);
                    }
                } else {
                    if(rt->right) {
                        addParticle(rt->right, particle, depth + 1);
                    } else {
                        rt->positionsRight.push_back(&particle);
                    }
                }
            }
        }
    }

    void drawRec(KDNode* root, int depth, int minx, int miny, int maxx, int maxy) {
        if(root) {
            int cd = depth % 2;
            if(cd == 0) {
                line(root->point.x, miny, root->point.x, maxy);
                drawRec(root->left, depth + 1, minx, miny, root->point.x, maxy);
                drawRec(root->right, depth + 1, root->point.x, miny, maxx, maxy);
            } else {
                line(minx, root->point.y, maxx, root->point.y);
                drawRec(root->left, depth + 1, minx, miny, maxx, root->point.y);
                drawRec(root->right, depth + 1, minx, root->point.y, maxx, maxy);
            }
        }
    }

    void updateParticles(KDNode* root) {
        if(root) {
            if(root->left)
                updateParticles(root->left);
            else {
                for (auto& elem : root->positionsLeft) {
                    elem->update();
                    elem->draw();
                }
                collisions(root->positionsLeft);
            }

            if(root->right)
                updateParticles(root->right);
            else {
                for (auto& elem : root->positionsRight) {
                    elem->update();
                    elem->draw();
                }
                collisions(root->positionsRight);
            }
        }
    }
public:

    KDTree(list<Particle>& pc): pc(pc), root(nullptr) {}
    //KDTree() : root(nullptr) {}

    void insert(Point point) {
        insertRec(root, point, 0);
    }
    void addParticle(Particle &particle) {
        addParticle(root, particle, 0);
    }
    void updateParticles() {
        updateParticles(root);
    }
    void draw() {
        drawRec(root, 0, 0, 0, 800, 600);
    }
};

int main() {

    //KDTree k;
    //k.insert(Point(400, 300));
    list<Particle> p;
    p.push_front(Particle(100, 200, 1.0, 1.0));
    p.push_front(Particle(200, 200, -1.0, 1.0));
    p.push_front(Particle(500, 400, 1.0, -1.0));
    KDTree k(p);
    initwindow(800,600);
    while(!kbhit()){

        //k.insert(Point(400, 300));
        k.draw();
        //for (auto& pp : p) {
            //k.addParticle(pp);
        //}
        //k.updateParticles();
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x;
            int y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            k.insert(Point(x, y));
        }
        delay(16);
        cleardevice();
    }
    getch();
    closegraph();
    return 0;
}

