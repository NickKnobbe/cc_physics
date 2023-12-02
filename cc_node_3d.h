#ifndef CC_NODE_3D
#define CC_NODE_3D

#include <godot_cpp/classes/node3d.hpp>
#include <circle_coll.h>
#include <node_internal.h>
#include <cc_physics_engine.h>

namespace godot {
    class CCNode3D : public Node3D {
        GDCLASS(CCNode3D, Node3D)

        private:
        double time_passed;

        protected:
        bool initialized = false;

        static void _bind_methods();

        public:
        Node3D* owning_node;
        NodeInternal* node_internal;

        CCNode3D();
        ~CCNode3D();

        void _process(double delta) override;

        void initialize(Node3D* owner, int id, Vector2 _position);

        Node3D* get_owning_node() const;
        void set_owning_node(Node3D* const direction);

        Vector2 get_velocity() const;
        void set_velocity(const Vector2 vel);

        void add_circle_coll(const Vector2 _center_offset, const float _radius);
        std::vector<CircleColl*> get_circle_colls();

        void add_behavior_controller(int selection);

        void give_to_engine(CCPhysicsEngine* engine);
    };
}

#endif