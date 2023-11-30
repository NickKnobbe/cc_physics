#ifndef CIRCLE_COLL_H
#define CIRCLE_COLL_H

#include <v2.h>

class CircleColl {
    private:

    public:
    V2 position;
    V2 center_offset;
    float radius;
    float radius_squared;
    int owner_id;

    CircleColl();
    CircleColl(V2 _center_offset, float _radius, int _owner_id);
    ~CircleColl();

    bool is_colliding_with(CircleColl* other);
};

#endif