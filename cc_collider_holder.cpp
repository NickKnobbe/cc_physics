#include "cc_collider_holder.h"

using namespace godot;

CCColliderHolder::CCColliderHolder() {
    held_colliders = std::vector<CircleColl*>();
}

CCColliderHolder::~CCColliderHolder() {}

void CCColliderHolder::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_input_direction"), &CCColliderHolder::get_input_direction);
    ClassDB::bind_method(D_METHOD("set_input_direction", "direction"), &CCColliderHolder::set_input_direction);
    ClassDB::add_property("CCColliderHolder", PropertyInfo(Variant::VECTOR2, "input_direction"), "set_input_direction", "get_input_direction");
    ClassDB::bind_method(D_METHOD("initialize", "owner", "_owner_id", "_position"), &CCColliderHolder::initialize);
    ClassDB::bind_method(D_METHOD("add_circle_coll", "_center_offset", "_radius"), &CCColliderHolder::add_circle_coll);
}

void CCColliderHolder::initialize(Node3D* owner, int _owner_id, Vector2 _position) {
    intialized = true;
    owning_node = owner;
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

Vector2 CCColliderHolder::get_input_direction() const {
    Vector2 inp = Vector2(input_direction.x, input_direction.y);
    return inp;
}

void CCColliderHolder::set_input_direction(const Vector2 direction) {
    input_direction = V2(direction.x, direction.y);
}

void CCColliderHolder::set_input_direction_v2(const V2 direction) {
    input_direction = direction;
}

void CCColliderHolder::add_circle_coll(const Vector2 _center_offset, const float _radius) {
    CircleColl coll = CircleColl(V2(_center_offset.x, _center_offset.y), _radius, this->owner_id);
}

// todo : evaluate safety, speed, etc of return
std::vector<CircleColl*> CCColliderHolder::get_circle_colls() {
    return held_colliders;
}