//
// Created by leo on 2020/2/22.
//

#include "Main.hpp"
#include "HUD.hpp"
#include "Mob.hpp"
#include "Player.hpp"
#include <PackedScene.hpp>
#include <Ref.hpp>
#include <Timer.hpp>
#include <random>

using namespace godot;

void Main::onScoreTimerTimeout() {
    HUD &hud = *(HUD *) get_node( "HUD" );
    hud.refreshScore( ++score );
}

void Main::onMessageOver() {
    HUD &  hud        = *(HUD *) get_node( "HUD" );
    Timer &mobTimer   = *(Timer *) get_node( "MobTimer" );
    Timer &scoreTimer = *(Timer *) get_node( "ScoreTimer" );

    switch ( state ) {
    case READY: {
        mobTimer.start();
        scoreTimer.start();
        state = GAMING;
        break;
    };
    case GAME_OVER: {
        hud.resetMenu();
        state = MENU;
        break;
    };
    default: {
    }
    }
}

void Main::onMobTimerTimeout() {
    Ref<PackedScene> mobScene   = SceneList[ 0 ];
    Vector2          screenSize = get_viewport_rect().size;
    Mob *            mob        = (Mob *) ( ( *mobScene )->instance() );

    add_child( mob );

    // Calculate Random position & velocity on Edges
    static std::default_random_engine  e;
    std::uniform_int_distribution<int> posDistrib(
        0, 2 * ( screenSize.x + screenSize.y ) - 1 );
    std::uniform_real_distribution<float> velDistrib(
        mob->get( "speed/min_speed" ), mob->get( "speed/max_speed" ) );
    std::uniform_real_distribution<float> dirDistrib( -Math_PI / 4,
                                                      Math_PI / 4 );

    Vector2 vel, pos;
    if ( int posPix = posDistrib( e ); posPix < screenSize.x ) { // Up Edge
        pos = Vector2( posPix, 0 );
        vel = Vector2( 0, 1 );
    } else if ( posPix < screenSize.x + screenSize.y ) { // right edge
        pos = Vector2( screenSize.x, posPix - screenSize.x );
        vel = Vector2( -1, 0 );
    } else if ( posPix < 2 * screenSize.x + screenSize.y ) { // bottom edge
        pos = Vector2( 2 * screenSize.x + screenSize.y - posPix, screenSize.y );
        vel = Vector2( 0, -1 );
    } else { // left edge
        pos = Vector2( 0, 2 * ( screenSize.x + screenSize.y ) - posPix );
        vel = Vector2( 1, 0 );
    }

    float dir = dirDistrib( e );
    vel       = vel.rotated( dir );
    mob->set_position( pos );
    mob->set_linear_velocity( vel * velDistrib( e ) );
    mob->set_rotation( vel.angle() );
}

void Main::onPlayerBodyEntered() {
    constexpr const char *gameOverMessage = "Game Over";

    HUD &  hud        = *(HUD *) get_node( "HUD" );
    Timer &mobTimer   = *(Timer *) get_node( "MobTimer" );
    Timer &scoreTimer = *(Timer *) get_node( "ScoreTimer" );

    Player &player = *(Player *) get_node( "Player" );
    player.hide();

    mobTimer.stop();
    scoreTimer.stop();

    hud.showMessage( gameOverMessage );

    state = GAME_OVER;
}

void Main::onStartButtonPressed() {
    HUD &                 hud          = *(HUD *) get_node( "HUD" );
    Player &              player       = *(Player *) get_node( "Player" );
    constexpr const char *readyMessage = "Ready!";

    player.set_position( get_viewport_rect().size / 2 );
    player.show();
    hud.hideStartButton();
    hud.showMessage( readyMessage );
    hud.refreshScore( score = 0 );
    state = READY;
}
