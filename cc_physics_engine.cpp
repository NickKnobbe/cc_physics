#include "cc_physics_engine.h"
#include <cc_circle_collider.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void CCPhysicsEngine::_bind_methods() {
    ClassDB::bind_method(D_METHOD("track_collider_holder"), &CCPhysicsEngine::track_collider_holder);
    ClassDB::bind_method(D_METHOD("initialize", "time_per_custom_process"), &CCPhysicsEngine::initialize);
}

CCPhysicsEngine::CCPhysicsEngine() {
    trackedCollHolders = std::vector<CCColliderHolder*>();
    trackedColls = std::vector<CircleColl*>();
    potentialCollisions = std::vector<CircleColl*>();
    confirmedCollisions = std::vector<CircleColl*>();
}

CCPhysicsEngine::~CCPhysicsEngine() {
    // cleanup
}

void CCPhysicsEngine::initialize(double time_per_custom_process) {
    time_per_process = time_per_custom_process;
    initialized = true;
    UtilityFunctions::print(Variant("CC_PHYS: Custom physics engine initialized!"));
}

void CCPhysicsEngine::_process(double delta) {
    if (!Engine::get_singleton()->is_editor_hint() && initialized) {
        time_passed += delta;

        for (auto& [key, value] : idToHolderMap) {
            if (value->owning_node) {
                Vector3 pos = value->owning_node->get_position();
                Vector3 next_pos = Vector3
                    (
                        pos.x + value->input_direction.x * delta,
                        pos.y + value->input_direction.y * delta, 
                        pos.z
                    );
                value->owning_node->set_position(next_pos);
                V2 next_pos_v2 = V2(next_pos.x, next_pos.y);
                value->position = next_pos_v2;
                for (auto i : value->held_colliders) {
                    i->position = next_pos_v2 + i->center_offset;
                }
            }
        }

        while (time_since_last_process > time_per_process) {
            time_since_last_process -= time_per_process;
            custom_phys_process(time_per_process);
        }
    }
}

void CCPhysicsEngine::custom_phys_process(double delta) {
    broad_phase();
    narrow_phase();
    evaluate_phase();
}

void CCPhysicsEngine::track_collider_holder(CCColliderHolder* holder) {
    idToHolderMap[holder->owner_id] = holder;
    trackedCollHolders.push_back(holder);
    std::vector<CircleColl*> colls = holder->get_circle_colls();
    for (auto i : colls) {
        trackedColls.push_back(i);
    }
}

// Gather potentials collisions
void CCPhysicsEngine::broad_phase() {
    potentialCollisions.clear();
    for (auto i : trackedColls) {
        for (auto j : trackedColls) {
            if (i->owner_id != j->owner_id) {
                potentialCollisions.push_back(i);
                potentialCollisions.push_back(j);
            }
        }
    }
}

// Determine which object collided
void CCPhysicsEngine::narrow_phase() {
    confirmedCollisions.clear();
    
    CircleColl* waiting = nullptr;

    bool getOut = false;
    while (!potentialCollisions.empty()) {

        CircleColl* next = potentialCollisions.back();
        potentialCollisions.pop_back();

        if (waiting) {
            if (waiting->is_colliding_with(next)) {
                // confirmedCollisions.push_back(waiting);
                // confirmedCollisions.push_back(next);
                evaluate_collision(waiting, next);
                waiting = nullptr;
            }
        }
        else {
            waiting = next;
        }
    }
}

void CCPhysicsEngine::evaluate_collision(CircleColl* a, CircleColl* b) {
    UtilityFunctions::print(Variant("CC_PHYS: Collision encountered!"));
}

void CCPhysicsEngine::evaluate_phase() {
    while (!confirmedCollisions.empty()) {
    }
}
