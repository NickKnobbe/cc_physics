#include "circle_coll.h"

CircleColl::CircleColl() {
    center_offset = V2(0.0, 0.0);
    radius = 0.1;
}

CircleColl::CircleColl(V2 _center_offset, float _radius, int _owner_id) {
    center_offset = _center_offset;
    radius = _radius;
    owner_id = _owner_id;
    radius_squared = radius * radius;
}

CircleColl::~CircleColl() {}

bool CircleColl::is_colliding_with(CircleColl* other) {
    
}