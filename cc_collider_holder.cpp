#include "cc_collider_holder.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

CCColliderHolder::CCColliderHolder() {
    held_colliders = std::vector<CircleColl*>();
}

CCColliderHolder::~CCColliderHolder() {}

void CCColliderHolder::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize", "owner", "_owner_id", "_position"), &CCColliderHolder::initialize);
    ClassDB::bind_method(D_METHOD("add_circle_coll", "_center_offset", "_radius"), &CCColliderHolder::add_circle_coll);
}

void CCColliderHolder::initialize(Node3D* owner, int _owner_id, Vector2 _position) {
    initialized = true;
    owning_node = owner;
    if (!owning_node) {
        UtilityFunctions::print(Variant("CC_COLLIDER_HOLDER: Owning node uninitialized!"));
    }
    owner_id = _owner_id;
    position = V2(_position.x, _position.y);
}

void CCColliderHolder::_process(double delta) {
    // if (!Engine::get_singleton()->is_editor_hint() && initialized) {
    //     time_passed += delta;

    //     while (time_since_last_process > time_per_process) {
    //         time_since_last_process -= time_per_process;
    //         custom_phys_process(time_per_process);
    //     }
    // }
}

void CCColliderHolder::add_circle_coll(const Vector2 _center_offset, const float _radius) {
    CircleColl coll = CircleColl(V2(_center_offset.x, _center_offset.y), _radius, this->owner_id);
    held_colliders.push_back(&coll);
}

// todo : evaluate safety, speed, etc of return
std::vector<CircleColl*> CCColliderHolder::get_circle_colls() {
    return held_colliders;
}