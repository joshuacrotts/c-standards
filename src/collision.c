#include "../include/collision.h"


enum CollisionSide 
check_aabb_collision(entity_t* a, entity_t* b) {
    float w = 0.5f * (b->w + a->w);
    float h = 0.5f * (b->h + a->h);
    float dx = (b->x + b->w / 2.0f) - (a->x + a->w / 2.0f);
    float dy = (b->y + b->h / 2.0f) - (a->y + a->h / 2.0f);

    if (abs((int)dx) < w && abs((int)dy) < h) {
        float wy = w * dy;
        float hx = h * dx;

        if (wy >= hx) {
            if (wy >= -hx) {//top
                a->y = b->y - a->h;
                return SIDE_TOP;
            } else {//right
                a->x = b->x + b->w;
                return SIDE_RIGHT;
            }
        } else {
            if (wy >= -hx) {//left
                a->x = b->x - a->w;
                return SIDE_LEFT;
            } else {//bottom
                a->y = b->y + b->h;
                return SIDE_BOTTOM;
            }
        }
    }

    return SIDE_NONE;
}
