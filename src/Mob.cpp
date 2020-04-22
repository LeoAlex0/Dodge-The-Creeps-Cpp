//
// Created by leo on 2020/2/22.
//

#include "Mob.hpp"
#include <AnimatedSprite.hpp>
#include <random>

using namespace godot;

void Mob::_ready() {
    constexpr const char *            mobTypes[] = {"walk", "swim", "fly"};
    static std::default_random_engine e;
    static std::uniform_int_distribution<int> mobTypeDistribution(
        0, sizeof( mobTypes ) / sizeof( *mobTypes ) - 1 );

    MinSpeed = 250;
    MaxSpeed = 400;

    AnimatedSprite &animatedSprite =
        *(AnimatedSprite *) get_node( "AnimatedSprite" );
    animatedSprite.set_animation( mobTypes[ mobTypeDistribution( e ) ] );
}

void Mob::onScreenExited() { queue_free(); }
