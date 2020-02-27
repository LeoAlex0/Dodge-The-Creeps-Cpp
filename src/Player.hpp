#ifndef SCRIPTS_PLAYER_HPP
#define SCRIPTS_PLAYER_HPP

#include "Vector2.hpp"
#include <Area2D.hpp>
#include <Godot.hpp>
#include <InputEvent.hpp>

class Player : public godot::Area2D {
    GODOT_CLASS( Player, godot::Area2D );

  public:
    void        _init() {}
    static void _register_methods() {
        using namespace godot;

        register_property( "speed", &Player::Speed, 400 );

        register_method( "_process", &Player::_process );
        register_method( "_input", &Player::_input );
    }

    int            Speed   = 400;
    godot::Vector2 _target = godot::Vector2( 0, 0 );

    void _process( const float delta );
    void _input( const godot::Ref<godot::InputEvent> event );
};

#endif
