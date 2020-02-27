//
// Created by leo on 2020/2/22.
//

#include "HUD.hpp"
#include <Button.hpp>
#include <Label.hpp>
#include <Timer.hpp>

using namespace godot;

void HUD::onStartButtonPressed() {
    emit_signal( signalStartButtonPressedName );
}

void HUD::onMessageTimerTimeout() {
    Label &messageLabel = *(Label *) get_node( "MessageLabel" );
    messageLabel.hide();

    emit_signal( signalMessageOverName );
}

void HUD::showMessage( String message ) {
    Label &messageLabel = *(Label *) get_node( "MessageLabel" );
    Timer &messageTimer = *(Timer *) get_node( "MessageTimer" );

    messageLabel.show();
    messageLabel.set_text( message );
    messageTimer.start();
}

void HUD::resetMenu() {
    Label & messageLabel = *(Label *) get_node( "MessageLabel" );
    Button &startButton  = *(Button *) get_node( "StartButton" );

    startButton.show();
    messageLabel.set_text( get( "title" ) );
    messageLabel.show();
}

void HUD::refreshScore( int score ) {
    Label &scoreLabel = *(Label *) get_node( "ScoreLabel" );
    scoreLabel.set_text( std::to_wstring( score ).c_str() );
}

void HUD::hideStartButton() {
    Button &startButton = *(Button *) get_node( "StartButton" );
    startButton.hide();
}
