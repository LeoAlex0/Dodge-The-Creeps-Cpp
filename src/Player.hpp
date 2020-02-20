#include "Vector2.hpp"
#include <Area2D.hpp>
#include <Godot.hpp>

using namespace godot;

class Player : public Area2D {
    GODOT_CLASS( Player, Area2D );

  public:
    void        _init() {}
    static void _register_methods() {
        register_property<Player, int>( "Speed", &Player::Speed, 400 );

        register_method( "_ready", &Player::_ready );
        register_method( "_process", &Player::_process );
    }

    int     Speed = 400;
    Vector2 screen_size;

    void _ready();

    void _process( const float delta );
};
