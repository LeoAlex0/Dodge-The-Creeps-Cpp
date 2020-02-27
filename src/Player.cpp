#include "Player.hpp"
#include <AnimatedSprite.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <InputEventScreenTouch.hpp>

using namespace godot;

void Player::_input( const Ref<InputEvent> event ) {
    if (event->is_class("InputEventScreenTouch") && cast_to<InputEventScreenTouch>(event.ptr())->is_pressed()){
        _target = cast_to<InputEventScreenTouch>(event.ptr())->get_position();
    }
}

void Player::_process( const float delta ) {
    const Vector2   screen_size = get_viewport_rect().size;
    const Input &   input       = *Input::get_singleton();
    AnimatedSprite &animatedSpirite =
        *(AnimatedSprite *) get_node( "AnimatedSprite" );
//    Vector2 vel( input.is_action_pressed( "ui_right" ) -
//                     input.is_action_pressed( "ui_left" ),
//                 input.is_action_pressed( "ui_down" ) -
//                     input.is_action_pressed( "ui_up" ) );

    Vector2 vel = _target - get_position();

    if ( vel.length() > delta * Speed ) {
        vel = vel.normalized() * Speed;

        set_rotation(vel.angle()+Math_PI/2);
        animatedSpirite.play();
    } else {
        animatedSpirite.stop();
    }

    // Get
    Vector2 position = get_position() + vel * delta;
    // Clamp
    position.x = std::max( 0.f, std::min( screen_size.x, position.x ) );
    position.y = std::max( 0.f, std::min( screen_size.y, position.y ) );
    // Set
    set_position( position );

//    if ( vel.x != 0 ) {
//        animatedSpirite.set_animation( "right" );
//        animatedSpirite.set_flip_v( false );
//        animatedSpirite.set_flip_h( vel.x < 0 );
//    }
//    if ( vel.y != 0 ) {
//        animatedSpirite.set_animation( "up" );
//        animatedSpirite.set_flip_v( vel.y > 0 );
//    }
}
