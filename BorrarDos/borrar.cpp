
void draw2(KDNode *root) {
        if(root) {
            if(root->left)
                draw2(root->left);
            else {
                for (auto it = root->positionsLeft.begin(); it != root->positionsLeft.end(); ++it) {
                    (*it).update();
                    if ((*it).position.x  > root->point.x && (*it).position.y  > root->point.y) {
                        Particle particle = (*it);
                        it = root->positionsLeft.erase(it);
                        add(particle);
                    }
                    (*it).draw();
                }
            }

            if(root->right)
                draw2(root->right);
            else {
                for (auto it = root->positionsRight.begin(); it != root->positionsRight.end(); ++it) {
                    (*it).update();
                    if ((*it).position.x  < root->point.x && (*it).position.y > root->point.y) {
                        Particle particle = (*it);
                        it = root->positionsLeft.erase(it);
                        add(particle);
                    }
                    (*it).draw();
                }
                //collisions(root->positionsRight);
            }
        }
    }
    void draw3(KDNode *root) {
        if(root) {
            if(root->left)
                draw2(root->left);
            else {
                collisions(root->positionsRight);
            }

            if(root->right)
                draw2(root->right);
            else {
                collisions(root->positionsRight);
            }
        }
    }
