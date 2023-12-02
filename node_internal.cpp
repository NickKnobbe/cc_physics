#include "node_internal.h"
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

NodeInternal::NodeInternal() {
    circle_colliders = std::vector<CircleColl>();
    controllers = std::vector<BehaviorController>();
}

NodeInternal::~NodeInternal() {
    
}

void NodeInternal::add_circle_coll(const godot::Vector2 _center_offset, const float _radius) {
    CircleColl coll = CircleColl(V2(_center_offset.x, _center_offset.y), _radius, this->id);
    circle_colliders.push_back(coll);
}

// todo : evaluate safety, speed, etc of return
std::vector<CircleColl> NodeInternal::get_circle_colls() {
    return circle_colliders;
}