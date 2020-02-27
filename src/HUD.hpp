//
// Created by leo on 2020/2/22.
//

#ifndef SCRIPTS_HUD_HPP
#define SCRIPTS_HUD_HPP

#include <CanvasLayer.hpp>
#include <Godot.hpp>

class HUD : public godot::CanvasLayer {
    GODOT_CLASS( HUD, godot::CanvasLayer );

  public:
    void _init() {}

    static void _register_methods() {
        using namespace godot;

        register_signal<HUD>( signalStartButtonPressedName );
        register_signal<HUD>( signalMessageOverName );

        register_property<HUD, String>( "title", &HUD::title,
                                        "Dodge the Creeps!" );
        register_method( "_on_StartButton_pressed",
                         &HUD::onStartButtonPressed );
        register_method( "_on_MessageTimer_timeout",
                         &HUD::onMessageTimerTimeout );
        register_method( "show_message", &HUD::showMessage );
        register_method( "reset_menu", &HUD::resetMenu );
        register_method( "refresh_score", &HUD::refreshScore );
        register_method( "hide_start_button", &HUD::hideStartButton );
    }

    void showMessage( godot::String message );
    void hideStartButton();
    void resetMenu();
    void refreshScore( int score );

    void onMessageTimerTimeout();

    void onStartButtonPressed();

    static constexpr const char *signalStartButtonPressedName =
        "start_button_pressed";
    static constexpr const char *signalMessageOverName = "message_over";
    godot::String                title                 = "Dodge the Creeps!";
};

#endif // SCRIPTS_HUD_HPP
