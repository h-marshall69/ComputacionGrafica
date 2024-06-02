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
};

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

    void viewTree(unique_ptr<Knode>&root, int depth) {
        if(root) {
            int cd = depth % 2;
            if(cd == 0) {
                cout << "x = " << root->partition << endl;
            } else {
                cout << "y = " << root->partition << endl;
            }
            if (!root->particles.empty()) {
                root->particles[0]->position.x = 10;
                for (auto& particle : root->particles) {
                    cout << particle->position.x << ":" << particle->position.y << " ";
                }
                cout << endl;
            } else {
                cout << "Nones\n";
            }
            viewTree(root->left, depth + 1);
            viewTree(root->right, depth + 1);
        }
    }
public:
    unique_ptr<Knode> root;
    Kdtree() : root(nullptr) {}
    void insert(vector<Particle*>& particles) {
        //vector<Particle*> particlePtrs;
        //for (auto& particle : particles) {
            //particlePtrs.push_back(&particle);
        //}
        insertwo(root, particles, 0);
    }
    void view() {
        viewTree(root, 0);
    }
};

int main() {
    vector<Particle*> particles;
    particles.push_back(new Particle(500, 400, 1.0, -1.0));
    particles.push_back(new Particle(100, 200, -1.0, 1.0));
    particles.push_back(new Particle(200, 200, -1.0, 1.0));
    particles.push_back(new Particle(465, 253, -1.0, 1.0));
    particles.push_back(new Particle(134, 543, -1.0, 1.0));

    Kdtree kd;
    kd.insert(particles);
    kd.view();
    cout << endl;
    for(auto & particle: particles) {
        cout << particle->position.x << ":" << particle->position.y << " ";
    }
    return 0;
}
