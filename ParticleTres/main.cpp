#include <iostream>
#include <winbgim.h>
#include <memory>
#include <math.h>
#include <vector>
#include <memory>
#include <algorithm>
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
    void draw() {
        circle(position.x, position.y, radio);
    }
};

double distancia(const Point& a, const Point& b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

class Knode {
public:
    Point point;
    double partition;
    unique_ptr<Knode> left;
    unique_ptr<Knode> right;
    vector<Particle*> particles;  // Usar punteros a partículas en lugar de objetos Particle
    Knode(double partition) : partition(partition), left(nullptr), right(nullptr) {}
    explicit Knode(vector<Particle*>& particles) : particles(move(particles)), left(nullptr), right(nullptr) {}
};

class Kdtree{
private:
    void insertwo(unique_ptr<Knode>&root, vector<Particle*>& particles, int depth) {
        if(particles.size() > 2) {
            int cd = depth % 2;
            if(cd == 0) {
                sort(particles.begin(), particles.end(), [](const Particle* a, const Particle* b) {
                    return a->position.x < b->position.x;
                });
                //double partition = (particles[0].position.x + particles[particles.size() - 1].position.x)/2;
                //vector<Particle&> left;
                //vector<Particle&> right;
                double partition = particles[particles.size() / 2]->position.x;
                root = make_unique<Knode>(partition);
                vector<Particle*> left(particles.begin(), particles.begin() + particles.size() / 2);
                vector<Particle*> right(particles.begin() + particles.size() / 2, particles.end());
                insertwo(root->left, left, depth + 1);
                insertwo(root->right, right, depth + 1);
            } else {
                sort(particles.begin(), particles.end(), [](const Particle* a, const Particle* b) {
                    return a->position.y < b->position.y;
                });
                double partition = particles[particles.size() / 2]->position.y;
                root = make_unique<Knode>(partition);
                vector<Particle*> left(particles.begin(), particles.begin() + particles.size() / 2);
                vector<Particle*> right(particles.begin() + particles.size() / 2, particles.end());
                insertwo(root->left, left, depth + 1);
                insertwo(root->right, right, depth + 1);
            }
        } else {
            root = make_unique<Knode>(particles);
            root->partition = 0.0;
        }
    }

    void viewTree(unique_ptr<Knode>& root, int depth) {
        if (root) {
            if (!root->particles.empty()) {
                if (root->particles.size() > 1 && distancia(root->particles[0]->position, root->particles[1]->position) < 40) { // Collision radius
                    root->particles[0]->velocity.x = -root->particles[0]->velocity.x;
                    root->particles[0]->velocity.y = -root->particles[0]->velocity.y;
                    root->particles[1]->velocity.x = -root->particles[1]->velocity.x;
                    root->particles[1]->velocity.y = -root->particles[1]->velocity.y;
                }
            }
            viewTree(root->left, depth + 1);
            viewTree(root->right, depth + 1);
        }
    }

    void drawTree(unique_ptr<Knode>& root, int depth, int minx, int miny, int maxx, int maxy) {
        if(root) {
            int cd = depth % 2;
            if(cd == 0) {
                line(root->partition, miny, root->partition, maxy);
                drawTree(root->left, depth + 1, minx, miny, root->partition, maxy);
                drawTree(root->right, depth + 1, root->partition, miny, maxx, maxy);
            } else {
                line(minx, root->partition, maxx, root->partition);
                drawTree(root->left, depth + 1, minx, miny, maxx, root->partition);
                drawTree(root->right, depth + 1, minx, root->partition, maxx, maxy);
            }
        }
    }
public:
    unique_ptr<Knode> root;
    Kdtree() : root(nullptr) {}
    ~Kdtree() {root = nullptr;}
    void insert(vector<Particle*>& particles) {
        insertwo(root, particles, 0);
    }
    void view() {
        viewTree(root, 0);
    }
    void draw() {drawTree(root, 0, 0, 0, 800, 600);}
};

int main() {
    vector<Particle*> particles;
    particles.push_back(new Particle(500, 400, 1.0, -1.0));
    particles.push_back(new Particle(100, 200, -1.0, 1.0));
    particles.push_back(new Particle(200, 200, -1.0, 1.0));
    particles.push_back(new Particle(321, 253, -1.0, 1.0));
    particles.push_back(new Particle(134, 400, -1.0, -1.0));
    particles.push_back(new Particle(465, 153, 1.0, 1.0));
    particles.push_back(new Particle(134, 40, 1.0, -1.0));

    initwindow(800, 600);
    while (!kbhit()) {
        Kdtree kd;
        kd.insert(particles);
        kd.view();
        kd.draw();
        for (auto& particle : particles) {
            particle->draw();
            particle->update();
        }
        delay(16);
        cleardevice();
    }
    getch();
    closegraph();
    return 0;
}
