#include "Player.hpp"
#include <AnimatedSprite.hpp>
#include <Input.hpp>

void Player::_ready() { screen_size = get_viewport_rect().size; }

void Player::_process(const float delta) {
    const Input &input = *Input::get_singleton();
    AnimatedSprite &animatedSpirite =
            *(AnimatedSprite *) get_node("AnimatedSprite");
    Vector2 vel(int(input.is_action_pressed("ui_right")) -
                int(input.is_action_pressed("ui_left")),
                int(input.is_action_pressed("ui_down")) -
                int(input.is_action_pressed("ui_up")));

    if (vel.length_squared() > 0) {
        vel = vel.normalized() * Speed;

        // Get
        Vector2 position = get_position() + vel * delta;
        // Clamp
        position.x = std::max(0.f, std::min(screen_size.x, position.x));
        position.y = std::max(0.f, std::min(screen_size.y, position.y));
        // Set
        set_position(position);

        animatedSpirite.play();
    } else {
        animatedSpirite.stop();
    }

    if (vel.x != 0) {
        animatedSpirite.set_animation("right");
        animatedSpirite.set_flip_v(false);
        animatedSpirite.set_flip_h(vel.x < 0);
    }
    if (vel.y != 0) {
        animatedSpirite.set_animation("up");
        animatedSpirite.set_flip_v(vel.y > 0);
    }
}
