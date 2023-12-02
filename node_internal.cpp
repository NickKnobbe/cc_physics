#include "node_internal.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

NodeInternal::NodeInternal() {
    circle_colliders = std::vector<CircleColl*>();
}

NodeInternal::~NodeInternal() {}

void NodeInternal::add_circle_coll(const Vector2 _center_offset, const float _radius) {
    CircleColl coll = CircleColl(V2(_center_offset.x, _center_offset.y), _radius, this->id);
    circle_colliders.push_back(&coll);
}

// todo : evaluate safety, speed, etc of return
std::vector<CircleColl*> NodeInternal::get_circle_colls() {
    return circle_colliders;
}