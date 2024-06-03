#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <memory>
#include <winbgim.h>
#include <functional>
using namespace std;

void linea(int xini, int yini, float angulo, int largo) {
    int x, y;
    x = largo * cos(angulo * M_PI / 180) + xini;
    y = largo * sin(angulo * M_PI / 180) + yini;
    line(xini, yini, x, y);
}

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
    float angulo;
    int inc;

    Particle(double x, double y, double vx, double vy): position(x, y), velocity(vx, vy) {
        angulo = 0;
        inc = 1;
        radius = 10;
    }
    void update() {
        position.x += velocity.x;
        position.y += velocity.y;
        angulo += inc;

        if (position.x - radius < 0 || position.x + radius > 800)
            velocity.x = -velocity.x;
        if (position.y - radius < 0 || position.y + radius > 600)
            velocity.y = -velocity.y;
        if (angulo < 0 || angulo > 45)
            inc = -inc;
    }
    void draw(int color = RED) {
        //circle(position.x, position.y, radius);
        setcolor(color);
        arc(position.x , position.y , angulo, 360 - angulo, radius);
        linea(position.x, position.y, angulo, radius);
        linea(position.x, position.y, 360 - angulo, radius);
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
    Particle* particles; // Cambiado de vector a puntero único de Particle
    std::unique_ptr<BvhNode> left;
    std::unique_ptr<BvhNode> right;

    BvhNode() : particles(nullptr), left(nullptr), right(nullptr) {}
};

class BVHTree {
private:
    void insertBvh(std::unique_ptr<BvhNode>& root, std::vector<Particle*>& particles, int start, int end) {
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

            root = std::make_unique<BvhNode>();
            if (end - start == 1) {
                root->particles = particles[start]; // Cambiado para asignar un solo puntero en lugar de un vector de punteros
                root->box = AABB(particles[start]->position.x - particles[start]->radius,
                                    particles[start]->position.x + particles[start]->radius,
                                    particles[start]->position.y - particles[start]->radius,
                                    particles[start]->position.y + particles[start]->radius);
            } else {
                insertBvh(root, particles, start, end);
            }
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
    std::unique_ptr<BvhNode> root;

    BVHTree() : root(nullptr) {}
    ~BVHTree() {}
    void collectParticles(std::unique_ptr<BvhNode>& root, vector<Particle*>& particles) {
        if (!root) return;
        if (root->particles) {
            particles.push_back(root->particles);
        } else {
            collectParticles(root->left, particles);
            collectParticles(root->right, particles);
        }
    }

    void updateVelocities(std::unique_ptr<BvhNode>& root) {
        if (!root) {
            return;
        }

        if (root->left && root->right) {
            updateVelocities(root->left);
            updateVelocities(root->right);

            if (root->left->box.overlaps(root->right->box)) {
                vector<Particle*> leftParticles, rightParticles;
                collectParticles(root->left, leftParticles);
                collectParticles(root->right, rightParticles);

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
    }

    void insert(std::vector<Particle*>& particles) {
        insertBvh(root, particles, 0, particles.size());
    }
    void draw() {drawBox(root);}
    void checkAllCollisions(std::unique_ptr<BvhNode>& left, std::unique_ptr<BvhNode>& right) {
        vector<Particle*> leftParticles, rightParticles;
        std::function<void(std::unique_ptr<BvhNode>&, vector<Particle*>&)> collectLeafParticles =
        [&](std::unique_ptr<BvhNode>& node, vector<Particle*>& particles) {
            if (node && !node->left && !node->right && node->particles) {
                particles.push_back(node->particles);
            } else {
                if (node->left) collectLeafParticles(node->left, particles);
                if (node->right) collectLeafParticles(node->right, particles);
            }
        };

        collectLeafParticles(left, leftParticles);
        collectLeafParticles(right, rightParticles);

        for (auto lp : leftParticles) {
            for (auto rp : rightParticles) {
                double dx = lp->position.x - rp->position.x;
                double dy = lp->position.y - rp->position.y;
                double distance = sqrt(dx * dx + dy * dy);
                if (distance < (lp->radius + rp->radius)) {
                    // Colisión detectada, actualizar velocidades
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
    void checkOverlaps(std::unique_ptr<BvhNode>& root) {
        if (root) {
            if (root->left && root->right && root->left->box.overlaps(root->right->box)) {
                checkAllCollisions(root->left, root->right);
                //return;
            }
            checkOverlaps(root->left);
            checkOverlaps(root->right);
        }
    }
    void collision() {
        //updateVelocities(root);
        checkOverlaps(root);
    }
};

int main() {
    std::vector<Particle*> particles;
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
            int numParticulas = particles.size();

            if (ismouseclick(WM_LBUTTONDOWN)) {
                int x, y;
                getmouseclick(WM_LBUTTONDOWN, x, y);
                //bvhTree.addParticle(x, y);
                particles.push_back(new Particle(x, y, 0.0, 0.0));
                clearmouseclick(WM_LBUTTONDOWN);
            }
            BVHTree bvhTree;

            bvhTree.insert(particles);
            //bvhTree.draw();
            bvhTree.collision();
            for (auto& particle : particles) {
                particle->draw();
                particle->update();
            }
            delay(16);
            cleardevice();
            string mensaje = "Particulas: " + to_string(numParticulas);
            char *cstr = new char[mensaje.length() + 1];
            strcpy(cstr, mensaje.c_str());
            outtextxy(10, 10, cstr);
            delete[] cstr;
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

