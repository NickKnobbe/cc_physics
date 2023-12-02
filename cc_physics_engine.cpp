#include "cc_physics_engine.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <behavior_controller.h>

using namespace godot;

void CCPhysicsEngine::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize", "time_per_custom_process", "time_per_ai_process"), &CCPhysicsEngine::initialize);
    ClassDB::bind_method(D_METHOD("set_diagnosis", "diagnosis_on"), &CCPhysicsEngine::set_diagnosis);
}

CCPhysicsEngine::CCPhysicsEngine() {
    frames_between_checks = 300; // ~5 seconds
    // Note that at one point, the difference between the engine starting or not 
    // was the instantiation of the custom CycleList type in the constructor.
    //trackedCollHolders = CycleList<CCColliderHolder*>();//std::vector<CCColliderHolder*>();
    //trackedCollHolders.reserve(COLL_HOLDER_CAPACITY);
    trackedColls = std::vector<CircleColl>();
    potentialCollisions = std::vector<CircleColl>();
    confirmedCollisions = std::vector<CircleColl>();
}

CCPhysicsEngine::~CCPhysicsEngine() {
    // cleanup
}

void CCPhysicsEngine::initialize(double time_per_custom_process, double time_per_ai_process) {
    physics_process_timer = BasicTimer(time_per_custom_process);
    ai_process_timer = BasicTimer(time_per_ai_process);
    initialized = true;
    UtilityFunctions::print(Variant("CC_PHYS: Custom physics engine initialized!"));
}

void CCPhysicsEngine::_process(double delta) {
    if (!Engine::get_singleton()->is_editor_hint() && initialized) {
        int phys_ticks = physics_process_timer.process(delta);
        int ai_ticks = ai_process_timer.process(delta);

        while (phys_ticks > 0) {
            custom_phys_process(physics_process_timer.time_per_action);
            --phys_ticks;
        }
        
        while (ai_ticks > 0) {
            ai_process(ai_process_timer.time_per_action);
            --ai_ticks;
        }

        double progress = physics_process_timer.time_since_last_action;        

        for (auto& [key, value] : trackedObjects) {
            if (value.owning_game_node) {
                double zPos = value.owning_game_node->get_position().z;
                V2 next_pos = V2(
                    value.position.x + (progress * value.velocity.x), 
                    value.position.y + (progress * value.velocity.y)
                    );

                Vector3 commit_next_pos = Vector3
                (
                    next_pos.x,
                    next_pos.y, 
                    zPos
                );
                value.owning_game_node->set_position(commit_next_pos);
            }
            else {
                UtilityFunctions::print(Variant("CC_PHYS: Owning game node uninitialized!"));
            }
        }
        // Note that at one point a null reference exception caused the running game to not crash, but rather exit this function.
    }
}

void CCPhysicsEngine::set_diagnosis(bool _diagnosis_on) {
    diagnosis_on = _diagnosis_on;
}

void CCPhysicsEngine::custom_phys_process(double delta) {
    if (diagnosis_on) {
        ++frames_since_check;
        if (frames_since_check >= frames_between_checks) {
            run_diagnosis();
        }
    }

    // New positions from former velocity
    for (auto& [key, value] : trackedObjects) {
        if (value.owning_game_node) {
            //Vector3 before_pos = value.owning_game_node->get_position();

            // New positions from former velocity
            V2 beforePos = value.position;
            value.position.x += value.velocity.x * delta;
            value.position.y += value.velocity.y * delta;
        }
        else {
            UtilityFunctions::print(Variant("CC_PHYS: Owning game node uninitialized!"));
        }
    }

    // Collision evaluation
    //broad_phase();
    //narrow_phase();
    //evaluate_phase();

    // Next velocities calculated
    for (auto& [key, value] : trackedObjects) {
        if (value.owning_game_node) {
            // Keeps it zero before input for now
            value.velocity = V2(0.0, 0.0);
            
            // Velocity updates
            if (value.controllers.size() > 0) {
                value.velocity = value.velocity + value.controllers[0].input_direction;
            }
        }
        else {
            UtilityFunctions::print(Variant("CC_PHYS: Owning game node uninitialized!"));
        }
    }
}

void CCPhysicsEngine::ai_process(double delta) {

}

/* void CCPhysicsEngine::track_collider_holder(CCColliderHolder* holder) {
    idToHolderMap[holder->owner_id] = holder;
    //trackedCollHolders.push_back(holder);
    trackedCollHolders.fill_next(holder);
    std::vector<CircleColl*> colls = holder->get_circle_colls();
    for (auto i : colls) {
        trackedColls.push_back(i);
    }
}

void CCPhysicsEngine::track_controller(CCController* controller) {
    idToControllerMap[controller->owner_id] = controller;
    if (trackedIds)
    //trackedCollHolders.push_back(holder);
    trackedCollHolders.fill_next(holder);
    std::vector<CircleColl*> colls = holder->get_circle_colls();
    for (auto i : colls) {
        trackedColls.push_back(i);
    }
} */

// Gather potentials collisions
void CCPhysicsEngine::broad_phase() {
    potentialCollisions.clear();
    for (auto i : trackedColls) {
        for (auto j : trackedColls) {
            if (diagnosis_on) {
                ++broad_compare_since_check;
            }
            //if (i->owner_id != j->owner_id) {
                potentialCollisions.push_back(i);
                potentialCollisions.push_back(j);
            //}
        }
    }
    broad_count_since_check += potentialCollisions.size();
}

// Determine which object collided
void CCPhysicsEngine::narrow_phase() {
    confirmedCollisions.clear();
    
    CircleColl* waiting = nullptr;

    bool getOut = false;
    while (!potentialCollisions.empty()) {

        CircleColl next = potentialCollisions.back();
        potentialCollisions.pop_back();
        if (waiting) {
            if (waiting->is_colliding_with(&next)) {
                ++collision_compare_count_since_check;
                // confirmedCollisions.push_back(waiting);
                // confirmedCollisions.push_back(next);
                evaluate_collision(*waiting, next);
                waiting = nullptr;
            }
        }
        else {
            waiting = &next;
        }
    }
}

void CCPhysicsEngine::track_node_internal(NodeInternal& node_internal) {
    trackedObjects[node_internal.id] = node_internal;
}

void CCPhysicsEngine::evaluate_collision(CircleColl& a, CircleColl& b) {
    ++collision_eval_count_since_check;
    //UtilityFunctions::print(Variant("CC_PHYS: Collision encountered!"));
}

void CCPhysicsEngine::evaluate_phase() {
    //while (!confirmedCollisions.empty()) {
    //}
}

void CCPhysicsEngine::run_diagnosis() {
    // The string built like this and printed has been proven to work.
    // broad_compare_since_check = 1500;
    long avg_broad_compare_since_check = broad_compare_since_check / frames_between_checks;
    long avg_broad_count_since_check = broad_count_since_check / frames_between_checks;
    long avg_narrow_count_since_check = narrow_count_since_check / frames_between_checks;
    long avg_collision_compare_count_since_check = collision_compare_count_since_check / frames_between_checks; 
    long avg_collision_eval_count_since_check = collision_eval_count_since_check / frames_between_checks; 
    int objects_tracked = trackedObjects.size();
    String summary = 
    String(Variant("CC_PHYS Diagnosis (averages are per frame over frame section since the previous diagnosis)\n")) 
    + String(Variant("   \nTracked internal object count: ")) + UtilityFunctions::str(Variant(objects_tracked))
    //+ String(Variant(",   \nTracked collider count: ")) + UtilityFunctions::str(Variant(trackedColls.size()))
    + String(Variant(",   \nAverage broad compare since check: ")) + UtilityFunctions::str(Variant(avg_broad_compare_since_check))
    + String(Variant(",   \nAverage broad compare since check: ")) + UtilityFunctions::str(Variant(avg_broad_compare_since_check))
    + String(Variant(",  \nAverage broad count since check: ")) + UtilityFunctions::str(Variant(avg_broad_count_since_check))
    + String(Variant(",  \nAverage narrow count since check: ")) + UtilityFunctions::str(Variant(avg_narrow_count_since_check))
    + String(Variant(",  \nAverage collision compare count since check: ")) + UtilityFunctions::str(Variant(avg_collision_compare_count_since_check))
    + String(Variant(",  \nAverage collision evaluate count since check: ")) + UtilityFunctions::str(Variant(avg_collision_eval_count_since_check));
    UtilityFunctions::print(summary);
    broad_compare_since_check = 0;
    broad_count_since_check = 0;
    narrow_count_since_check = 0;
    collision_compare_count_since_check = 0;
    collision_eval_count_since_check = 0;
    frames_since_check = 0;
}