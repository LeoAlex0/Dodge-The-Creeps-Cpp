#ifndef SCRIPTS_PLAYER_HPP
#define SCRIPTS_PLAYER_HPP

#include "Vector2.hpp"
#include <Area2D.hpp>
#include <Godot.hpp>

class Player : public godot::Area2D {
    GODOT_CLASS( Player, godot::Area2D );

  public:
    void        _init() {}
    static void _register_methods() {
        using namespace godot;

        register_property( "speed", &Player::Speed, 400 );

        register_method( "_process", &Player::_process );
    }

    int Speed = 400;

    void _process( const float delta );
};

#endif
