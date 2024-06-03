#include <iostream>
#include <winbgim.h>
#include <math.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <cfloat>
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
    int radius;

    Particle(double x, double y, double vx, double vy): position(x, y), velocity(vx, vy) {
        radius = 10;
    }

    void update() {
        position.x += velocity.x;
        position.y += velocity.y;

        if (position.x - radius < 0 || position.x + radius > 800)
            velocity.x = -velocity.x;
        if (position.y - radius < 0 || position.y + radius > 600)
            velocity.y = -velocity.y;
    }
    void draw() {
        circle(position.x, position.y, radius);
    }
};

class AABB{
public:
    double xMin, yMin;
    double xMax, yMax;
    AABB() : xMin(0.0), xMax(0.0), yMin(0.0), yMax(0.0) {}
    AABB(double xMin, double xMax, double yMin, double yMax)
        : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}

    bool overlaps(const AABB& other) const {
        return xMin <= other.xMax && xMax >= other.xMin &&
               yMin <= other.yMax && yMax >= other.yMin;
    }
};

class BvhNode{
public:
    AABB box;
    //Particle* particle;
    vector<Particle*> particles;
    //BvhNode* left;
    //BvhNode* right;
    unique_ptr<BvhNode> left;
    unique_ptr<BvhNode> right;
    BvhNode() : left(nullptr), right(nullptr) {}
    explicit BvhNode(vector<Particle*>& particles) : particles(move(particles)), left(nullptr), right(nullptr) {}
};

class BVH{
private:
    void insertBvh(unique_ptr<BvhNode>& root, vector<Particle*>& particles, int start, int end) {
        if (start >= end) {
            return;
        }

        int mid = (start + end) / 2;

        std::nth_element(particles.begin() + start, particles.begin() + mid, particles.begin() + end,
                         [](Particle* a, Particle* b) { return a->position.x < b->position.x; });

        root = make_unique<BvhNode>();

        if (end - start == 1) {
            root->particles = particles;
            root->box = AABB(particles[start]->position.x - particles[start]->radius,
                             particles[start]->position.x + particles[start]->radius,
                             particles[start]->position.y - particles[start]->radius,
                             particles[start]->position.y + particles[start]->radius);
        } else {
            insertBvh(root->left, particles, start, mid);
            insertBvh(root->right, particles, mid, end);

            root->box = AABB(
                std::min(root->left->box.xMin, root->right->box.xMin),
                std::max(root->left->box.xMax, root->right->box.xMax),
                std::min(root->left->box.yMin, root->right->box.yMin),
                std::max(root->left->box.yMax, root->right->box.yMax)
            );
        }
    }
    void drawBox(unique_ptr<BvhNode>& root) {
        if(root) {
            rectangle(root->box.xMin, root->box.yMin, root->box.xMax,root->box.yMax);
            drawBox(root->left);
            drawBox(root->right);
        }
    }
public:
    //BvhNode* root;
    unique_ptr<BvhNode> root;
    BVH() : root(nullptr) {}
    ~BVH() {root = nullptr;}
    void insert(vector<Particle*>& particles) {
        insertBvh(root, particles, 0, particles.size());
    }
    void draw() {drawBox(root);}
};

int main() {
    vector<Particle*> particles;
    particles.push_back(new Particle(500, 400, 1.0, -1.0));
    particles.push_back(new Particle(100, 200, -1.0, 1.0));
    particles.push_back(new Particle(200, 200, -1.0, -1.0));
    particles.push_back(new Particle(321, 253, 1.0, -1.0));
    particles.push_back(new Particle(134, 400, -1.0, -1.0));
    particles.push_back(new Particle(465, 153, 1.0, 1.0));
    particles.push_back(new Particle(134, 40, 1.0, -1.0));
    if(false) {
        cout<<2;

    } else {
        initwindow(800, 600);
        while (!kbhit()) {
            BVH bvh;
            bvh.insert(particles);
            bvh.draw();
            for (auto& particle : particles) {
                particle->draw();
                particle->update();
            }
            delay(16);
            cleardevice();
        }
        getch();
        closegraph();
    }
    return 0;
}
