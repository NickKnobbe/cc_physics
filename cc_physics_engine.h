#ifndef CC_PHYSICS_ENGINE 
#define CC_PHYSICS_ENGINE

#include <godot_cpp/classes/sprite3d.hpp>
#include <node_internal.h>
#include <circle_coll.h>
#include <vector>
#include <unordered_map>
#include <cycle_list.h>
#include <cycle_queue.h>
#include <basic_timer.h>

namespace godot {
    class CCPhysicsEngine : public Node3D {
        GDCLASS(CCPhysicsEngine, Node3D)
        private:
        bool initialized = false;
        const int MAX_POTENTIAL_COLLISIONS = 1000000;
        const int COLL_HOLDER_CAPACITY = 100000;

        BasicTimer physics_process_timer;
        BasicTimer ai_process_timer;

        //CycleQueue<CCColliderHolder> toEvaluate;
        //CycleList<CCColliderHolder*> trackedCollHolders;
        std::vector<CircleColl*> trackedColls;
        std::vector<CircleColl*> potentialCollisions;
        std::vector<CircleColl*> confirmedCollisions;

        protected:
        bool diagnosis_on = false;
        std::unordered_map<int, NodeInternal*> trackedObjects;

        long frames_since_check = 0;
        int frames_between_checks = 300;
        long broad_compare_since_check = 0;
        long broad_count_since_check = 0;
        long narrow_count_since_check = 0;
        long collision_compare_count_since_check = 0;
        long collision_eval_count_since_check = 0;

        static void _bind_methods();

        public:
        CCPhysicsEngine();
        ~CCPhysicsEngine();

        void initialize(double time_per_custom_process);
        void set_diagnosis(bool _diagnosis_on);

        void _process(double delta) override;
        void custom_phys_process(double delta);
        void ai_process(double delta);

        //void track_collider(CCCircleCollider* node);
        void track_node_internal(NodeInternal* node_internal);

        void broad_phase();
        void narrow_phase();
        void evaluate_phase();
        void evaluate_collision(CircleColl* a, CircleColl* b);

        void run_diagnosis();
    };
}

#endif