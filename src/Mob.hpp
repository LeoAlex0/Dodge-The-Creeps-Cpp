#ifndef SCRIPTS_MOB_HPP
#define SCRIPTS_MOB_HPP

#include <Godot.hpp>
#include <RigidBody2D.hpp>

class Mob : public godot::RigidBody2D {
    GODOT_CLASS( Mob, godot::RigidBody2D );

  public:
    void _init() { }
    static void _register_methods() {
        using namespace godot;

        register_property( "speed/max_speed", &Mob::MaxSpeed, 400 );
        register_property( "speed/min_speed", &Mob::MinSpeed, 250 );

        register_method( "_ready", &Mob::_ready );
        register_method( "_on_Screen_exited", &Mob::onScreenExited );
    }

    void _ready();
    void onScreenExited();

    int MaxSpeed, MinSpeed;
};

#endif // SCRIPTS_MOB_HPP
