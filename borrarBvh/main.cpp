#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <memory>
#include <winbgim.h>
#include <functional>
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
        radius = 20;
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
    explicit AABB(double xMin, double xMax, double yMin, double yMax)
        : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}

    bool overlaps(const AABB& other) const {
        return xMin <= other.xMax && xMax >= other.xMin &&
               yMin <= other.yMax && yMax >= other.yMin;
    }
};

class BvhNode{
public:
    AABB box;
    Particle* particle;
    std::vector<Particle*> particles;
    std::unique_ptr<BvhNode> left;
    std::unique_ptr<BvhNode> right;

    BvhNode() : particle(nullptr) {}
    explicit BvhNode(std::vector<Particle*>& particles) : particles(std::move(particles)) {}
};

class BVHTree {
private:
    void insertBvh(unique_ptr<BvhNode>& root, vector<Particle*>& particles, int start, int end) {
        if (root) {
            int mid = (start + end) / 2;

            std::nth_element(particles.begin() + start, particles.begin() + mid, particles.begin() + end,
                             [](Particle* a, Particle* b) { return a->position.x < b->position.x; });

            insertBvh(root->left, particles, start, mid);
            insertBvh(root->right, particles, mid, end);

            root->box = AABB(
                std::min(root->left ? root->left->box.xMin : FLT_MAX, root->right ? root->right->box.xMin : FLT_MAX),
                std::max(root->left ? root->left->box.xMax : -FLT_MAX, root->right ? root->right->box.xMax : -FLT_MAX),
                std::min(root->left ? root->left->box.yMin : FLT_MAX, root->right ? root->right->box.yMin : FLT_MAX),
                std::max(root->left ? root->left->box.yMax : -FLT_MAX, root->right ? root->right->box.yMax : -FLT_MAX)
            );
        } else {
            if (start >= end) {
                return;
            }

            root = make_unique<BvhNode>();
            if (end - start == 1) {
                root->particles = particles;
                root->box = AABB(particles[start]->position.x - particles[start]->radius,
                                    particles[start]->position.x + particles[start]->radius,
                                    particles[start]->position.y - particles[start]->radius,
                                    particles[start]->position.y + particles[start]->radius);
            } else {
                insertBvh(root, particles, start, end);
            }
        }
    }
public:
    unique_ptr<BvhNode> root;

    BVHTree() : root(nullptr) {}
    ~BVHTree() {}



    void updateVelocities(BvhNode* node) {
        if (!node || (!node->left && !node->right)) {
            return;
        }

        if (node->left && node->right && node->left->box.overlaps(node->right->box)) {
            updateVelocities(node->left.get());
            updateVelocities(node->right.get());

            vector<Particle*> leftParticles, rightParticles;
            function<void(BvhNode*, vector<Particle*>&)> collectParticles = [&](BvhNode* n, vector<Particle*>& particles) {
                if (!n) return;
                if (n->particle) {
                    particles.push_back(n->particle);
                } else {
                    collectParticles(n->left.get(), particles);
                    collectParticles(n->right.get(), particles);
                }
            };

            collectParticles(node->left.get(), leftParticles);
            collectParticles(node->right.get(), rightParticles);

            for (auto lp : leftParticles) {
                for (auto rp : rightParticles) {
                    double dx = lp->position.x - rp->position.x;
                    double dy = lp->position.y - rp->position.y;
                    double distance = sqrt(dx * dx + dy * dy);
                    if (distance < (lp->radius + rp->radius)) {
                        // Update velocities
                        double nx = (rp->position.x - lp->position.x) / distance;
                        double ny = (rp->position.y - lp->position.y) / distance;

                        double tx = -ny;
                        double ty = nx;

                        double dpTan1 = lp->velocity.x * tx + lp->velocity.y * ty;
                        double dpTan2 = rp->velocity.x * tx + rp->velocity.y * ty;

                        double dpNorm1 = lp->velocity.x * nx + lp->velocity.y * ny;
                        double dpNorm2 = rp->velocity.x * nx + rp->velocity.y * ny;

                        double m1 = (dpNorm1 * (lp->radius - rp->radius) + 2.0 * rp->radius * dpNorm2) / (lp->radius + rp->radius);
                        double m2 = (dpNorm2 * (rp->radius - lp->radius) + 2.0 * lp->radius * dpNorm1) / (lp->radius + rp->radius);

                        lp->velocity.x = tx * dpTan1 + nx * m1;
                        lp->velocity.y = ty * dpTan1 + ny * m1;
                        rp->velocity.x = tx * dpTan2 + nx * m2;
                        rp->velocity.y = ty * dpTan2 + ny * m2;
                    }
                }
            }
        }
    }

    void insert(std::vector<Particle*>& particles) {
        insertBvh(root, particles, 0, particles.size());
    }

    void collision() {
        updateVelocities(root.get());
    }
};

int main() {
    std::vector<Particle*> particles = {
        new Particle(500.0, 400.0, 1.0, -1.0),
        new Particle(100.0, 200.0, -1.0, 1.0),
        new Particle(200.0, 200.0, -1.0, -1.0),
        new Particle(321.0, 253.0, 1.0, -1.0),
        new Particle(134, 400, -1.0, -1.0),
        new Particle(465, 153, 1.0, 1.0),
        new Particle(134, 40, 1.0, -1.0)
    };

    if(false) {
        cout<<2;

    } else {
        initwindow(800, 600);
        while (!kbhit()) {
            BVHTree bvhTree;

            bvhTree.insert(particles);
            bvhTree.collision();
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

    // Cleanup
    for (auto p : particles) {
        delete p;
    }

    return 0;
}
