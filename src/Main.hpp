//
// Created by leo on 2020/2/22.
//

#ifndef SCRIPTS_MAIN_HPP
#define SCRIPTS_MAIN_HPP

#include <Godot.hpp>
#include <Node2D.hpp>
#include <RandomNumberGenerator.hpp>

class Main : public godot::Node2D {
    GODOT_CLASS( Main, Node2D )
  public:
    void _init() {
        score = 0;
        state = MENU;
    }
    static void _register_methods() {
        using namespace godot;

        register_property( "score", &Main::score, 0 );
        register_property<Main, Array>( "mob_scene", &Main::SceneList,
                                        Array() );

        register_method( "_ready", &Main::_ready );
        register_method( "_on_ScoreTimer_timeout", &Main::onScoreTimerTimeout );
        register_method( "_on_HUD_message_over", &Main::onMessageOver );
        register_method( "_on_HUD_start_button_pressed",
                         &Main::onStartButtonPressed );
        register_method( "_on_MobTimer_timeout", &Main::onMobTimerTimeout );
        register_method( "_on_Player_body_entered",
                         &Main::onPlayerBodyEntered );
    }

    void onStartButtonPressed();
    void onScoreTimerTimeout();
    void onMessageOver();
    void onMobTimerTimeout();
    void onPlayerBodyEntered();
    void _ready();

    int score;
    enum State {
        MENU,
        READY,
        GAMING,
        GAME_OVER,
    } state;
    godot::Array                 SceneList;
    godot::RandomNumberGenerator *generator;
};

#endif // SCRIPTS_MAIN_HPP
