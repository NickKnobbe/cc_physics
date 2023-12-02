#include "behavior_controller.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/node3d.hpp>

BehaviorController::BehaviorController() {
    input_direction = V2();
}

BehaviorController::~BehaviorController() {}


void BehaviorController::initialize(godot::Node3D* owner, int _owner_id, godot::Vector2 _position) {
    initialized = true;
    owning_node = owner;
    if (!owning_node) {
        godot::UtilityFunctions::print(godot::Variant("CC_CONTROLLER: Owning node uninitialized!"));
    }
    owner_id = _owner_id;
    position = V2(_position.x, _position.y);
}

godot::Vector2 BehaviorController::get_input_direction() const {
    godot::Vector2 inp = godot::Vector2(input_direction.x, input_direction.y);
    return inp;
}

void BehaviorController::set_input_direction(const godot::Vector2 direction) {
    input_direction = V2(direction.x, direction.y);
}

void BehaviorController::set_input_direction_v2(const V2 direction) {
    input_direction = direction;
}