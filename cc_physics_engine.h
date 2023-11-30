#ifndef CC_PHYSICS_ENGINE 
#define CC_PHYSICS_ENGINE

#include <godot_cpp/classes/sprite3d.hpp>
#include <cc_circle_collider.h>
#include <cc_collider_holder.h>
#include <circle_coll.h>
#include <cc_node_3d.h>
#include <vector>
#include <map>

namespace godot {
    class CCPhysicsEngine : public Node3D {
        GDCLASS(CCPhysicsEngine, Node3D)
        private:
        bool initialized = false;
        const int MAX_POTENTIAL_COLLISIONS = 1000000;

        double time_passed;
        double time_since_last_process;
        double time_per_process;

        double amplitude;

        std::map<int, CCColliderHolder*> idToHolderMap; 
        std::vector<CCColliderHolder*> trackedCollHolders;
        std::vector<CircleColl*> trackedColls;
        std::vector<CircleColl*> potentialCollisions;
        std::vector<CircleColl*> confirmedCollisions;

        protected:
        static void _bind_methods();

        public:
        CCPhysicsEngine();
        ~CCPhysicsEngine();

        void initialize(double time_per_custom_process);

        void _process(double delta) override;
        void custom_phys_process(double delta);

        void track_collider(CCCircleCollider* node);
        void track_collider_holder(CCColliderHolder* holder);

        void broad_phase();
        void narrow_phase();
        void evaluate_phase();
        void evaluate_collision(CircleColl* a, CircleColl* b);
    };
}

#endif