#ifndef CC_CONTROLLER
#define CC_CONTROLLER

#include <godot_cpp/classes/node3d.hpp>
#include <circle_coll.h>
#include <cc_node_3d.h>

class BehaviorController {
    private:
    double time_passed;

    protected:
    bool initialized = false;

    static void _bind_methods();

    public:
    godot::Node3D* owning_node;
    int owner_id;

    V2 input_direction;
    V2 position;
    V2 velocity;
    V2 acceleration;

    BehaviorController();
    ~BehaviorController();

    void initialize(godot::Node3D* owner, int _owner_id, Vector2 _position);

    //CCNode3D* get_owning_node() const;
    //void set_owning_node(CCNode3D* const direction);

    Vector2 get_input_direction() const;
    void set_input_direction(const Vector2 direction);
    void set_input_direction_v2(const V2 direction);
};

#endif