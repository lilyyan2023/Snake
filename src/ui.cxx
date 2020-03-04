//
// Created by Anxin Guo on 2/29/20.
//

#include "ui.hxx"

UI::UI(Geometry geometry)
: model_(geometry)
, status_(Screen::begin)
, since_last_update(0)
{ }

void UI::draw(ge211::Sprite_set &set) {
    switch (status_){
        case begin:
            draw_begin(set);
            break;
        case gameplay:
            draw_gameplay(set);
            break;
        case pause:
            draw_pause(set);
            break;
        case levelup:
            draw_levelup(set);
    }
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

void UI::draw_begin(ge211::Sprite_set &set) {
    /// this causes crash
    set.add_sprite(ge211::Text_sprite("This is a game", {"sans.ttf", 20}),
                   {0,0}, 10);
}

void UI::draw_gameplay(ge211::Sprite_set &) {

}

void UI::draw_pause(ge211::Sprite_set &) {

}

void UI::draw_levelup(ge211::Sprite_set &) {

}


