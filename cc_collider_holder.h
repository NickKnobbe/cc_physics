#ifndef CC_COLLIDER_HOLDER
#define CC_COLLIDER_HOLDER

#include <godot_cpp/classes/node3d.hpp>
#include <circle_coll.h>

namespace godot {
    class CCColliderHolder : public Node3D {
        GDCLASS(CCColliderHolder, Node3D)

        private:
        double time_passed;

        protected:
        bool intialized = false;

        static void _bind_methods();

        public:
        Node3D* owning_node;
        int owner_id;

        std::vector<CircleColl*> held_colliders;

        V2 input_direction;
        V2 position;
        V2 velocity;
        V2 acceleration;

        CCColliderHolder();
        ~CCColliderHolder();

        static void _bind_methods();

        void _process(double delta) override;

        void initialize(Node3D* owner, int _owner_id, Vector2 _position);

        Node3D* get_owning_node() const;
        void set_owning_node(Node3D* const direction);

        Vector2 get_input_direction() const;
        void set_input_direction(const Vector2 direction);
        void set_input_direction_v2(const V2 direction);

        Vector2 get_velocity() const;
        void set_velocity(const Vector2 vel);

        void add_circle_coll(const Vector2 _center_offset, const float _radius);
        std::vector<CircleColl*> get_circle_colls();
    };
}

#endif