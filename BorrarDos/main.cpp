#include <iostream>
#include <winbgim.h>
#include <memory>
#include <cmath>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Point {
public:
    double x, y;
    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}
    bool operator!=(const Point& other) const {
        return x != other.x || y != other.y;
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

double distancia(const Point& a, const Point& b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

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

    void draw() const {
        circle(position.x, position.y, radio);
    }
};

class VPNode {
public:
    Particle* particle;
    VPNode* inside;
    VPNode* outside;
    double r;

    VPNode(Particle* particle) : particle(particle), inside(nullptr), outside(nullptr), r(0) {}
};

class VPTree {
private:
    VPNode* root;
    list<Particle>& particles;

    void insert(VPNode*& node, Particle* particle, double radio) {
        if (!node) {
            node = new VPNode(particle);
            node->r = radio;
            return;
        }

        double dist = distancia(node->particle->position, particle->position);
        if (dist <= (node->particle->radio + particle->radio)) {
            handleCollision(node->particle, particle);
        }

        if (dist < node->r) {
            insert(node->inside, particle, dist);
        } else {
            insert(node->outside, particle, dist);
        }
    }

    void handleCollision(Particle* p1, Particle* p2) {
        swap(p1->velocity.x, p2->velocity.x);
        swap(p1->velocity.y, p2->velocity.y);

        //particles.push_back(Particle((p1->position.x + p2->position.x) / 2, (p1->position.y + p2->position.y) / 2, -1.0, -1.0));
    }

public:
    VPTree(list<Particle>& particles) : particles(particles), root(nullptr) {}
    void insert(Particle* particle) {
        insert(root, particle, 60.0);
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    list<Particle> particles;
    for (int i = 0; i < 25; ++i) {
        double x = rand() % 800;
        double y = rand() % 600;
        double vx = (rand() % 100 / 50.0) - 1; // velocidad entre -1 y 1
        double vy = (rand() % 100 / 50.0) - 1; // velocidad entre -1 y 1
        particles.push_back(Particle(x, y, vx, vy));
    }
    initwindow(800, 600);

    while (!kbhit()) {
        VPTree tree(particles);
        for (auto& particle : particles) {
            tree.insert(&particle);
        }

        for (auto& particle : particles) {
            particle.draw();
            particle.update();
        }
        delay(16);
        cleardevice();
    }

    getch();
    closegraph();
    return 0;
}
