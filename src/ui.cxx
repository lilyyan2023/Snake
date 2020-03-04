//
// Created by Anxin Guo on 2/29/20.
//

#include "ui.hxx"

UI::UI(Geometry geometry)
: model_(geometry)
, status_(Screen::begin)
, since_last_update(0)
{ }

void UI::draw(ge211::Sprite_set &) {
    //todo: status; draw snake (tail), obstacle, wall; keep door and hole open
}

void UI::on_key(ge211::Key) {
    //todo: turn/pause
}

void UI::on_frame(double) {
    //todo: decide whether to update();
}

ge211::Color UI::get_color(int score) {
    //todo: color based on score。
}


