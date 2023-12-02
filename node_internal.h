#ifndef CC_NODE_INTERNAL 
#define CC_NODE_INTERNAL 

#include <godot_cpp/classes/node3d.hpp>
#include <circle_coll.h>

class godot::Node3D;
class godot::CCNode3D;
class BehaviorController;
class V2;

class NodeInternal {
private:
    double time_passed = 0;

protected:
    bool initialized = false;

public:
    int id;
    V2 position;
    
    godot::Node3D* owning_game_node;
    godot::CCNode3D* owning_node;

    std::vector<CircleColl*> circle_colliders;
    std::vector<BehaviorController*> controllers;

    NodeInternal();
    ~NodeInternal();

    void add_circle_coll(const Vector2 _center_offset, const float _radius);
    std::vector<CircleColl*> get_circle_colls();
};

#endif