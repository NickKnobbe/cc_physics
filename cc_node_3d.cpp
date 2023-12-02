#include "cc_node_3d.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <cc_physics_engine.h>
#include <behavior_controller.h>
#include <cc_util.h>

using namespace godot;

godot::CCNode3D::CCNode3D() {
    node_internal = new NodeInternal();
}

godot::CCNode3D::~CCNode3D() {
    if (node_internal) {
        delete node_internal;
    }
}

void godot::CCNode3D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize", "owner", "_owner_id", "_position"), &CCNode3D::initialize);
    ClassDB::bind_method(D_METHOD("add_circle_coll", "_center_offset", "_radius"), &CCNode3D::add_circle_coll);
    ClassDB::bind_method(D_METHOD("add_behavior_controller", "selection"), &CCNode3D::add_behavior_controller);
    ClassDB::bind_method(D_METHOD("give_to_engine", "engine"), &CCNode3D::give_to_engine);
}

void godot::CCNode3D::initialize(Node3D* owner, int _id, Vector2 _position) {
    node_internal->id = _id;
    node_internal->owning_node = this;
    node_internal->owning_game_node = owner;
    owning_node = owner;
    if (!owning_node) {
        CCUtil::printe("Collider owning node uninit");
    }
    node_internal->position = V2(_position.x, _position.y);
    initialized = true;
}

void godot::CCNode3D::_process(double delta) {
    // if (!Engine::get_singleton()->is_editor_hint() && initialized) {
    //     time_passed += delta;

    //     while (time_since_last_process > time_per_process) {
    //         time_since_last_process -= time_per_process;
    //         custom_phys_process(time_per_process);
    //     }
    // }
}

void godot::CCNode3D::add_circle_coll(const Vector2 _center_offset, const float _radius) {
    if (node_internal) {
        CircleColl coll = CircleColl(V2(_center_offset.x, _center_offset.y), _radius, node_internal->id);
        node_internal->circle_colliders.push_back(coll);
    }
}

void godot::CCNode3D::add_behavior_controller(int selection) {
    BehaviorController bc = BehaviorController();
    // todo remove
    bc.set_input_direction_v2(V2(0.4, 0.5));
    //BehaviorController* pt = &bc;
    // Note that it didn't work to just pass func(&var_name) to pass a pointer.
    // Instead, we had to do type* ptr = &var_name.
    // Ok and then later it did work... wtf

    // Doing a func(&var_name) will pass a pointer by value.
    node_internal->controllers.push_back(bc);
    UtilityFunctions::print(Variant("CC_PHYS AA!"));
}

// todo : evaluate safety, speed, etc of return
std::vector<CircleColl> godot::CCNode3D::get_circle_colls() {
    return node_internal->circle_colliders;
}

void godot::CCNode3D::give_to_engine(CCPhysicsEngine* engine) {
    if (node_internal) {
        engine->track_node_internal(*node_internal);
    }
}