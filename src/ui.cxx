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
            break;
    }
}

void UI::on_key(ge211::Key key) {
    if (status_ == begin || status_ == pause)
        status_ = gameplay;
    else if (status_ == gameplay && key == ge211::Key::code('q'))
        status_ = pause;
    //todo: other scenarios
}

void UI::on_frame(double elapsed) {
    switch (status_) {
        case gameplay:
            since_last_update += elapsed;
            if (since_last_update >= model_.geometry_.update_interval_) {
                since_last_update = 0;
                model_.update();
            }
            break;
        case levelup:
            since_last_update += elapsed;
            if (since_last_update >= model_.geometry_.update_interval_) {
                since_last_update = 0;
                level_up_count();
            }
            break;
        default:
            break;
    }
}

ge211::Color UI::get_color(int score) {
    //todo: color based on score
}

void UI::draw_begin(ge211::Sprite_set &set) {
    set.add_sprite(title_sprite,
                   {model_.geometry_.mid_x() - 200,
             model_.geometry_.mid_y() - 150}, 1);
    set.add_sprite(press_key_sprite,
                   {model_.geometry_.mid_x() - 130,
                    model_.geometry_.mid_y() + 160}, 1);
}

void UI::draw_gameplay(ge211::Sprite_set &set) {
    for (auto body : model_.snake_)
        set.add_sprite(body_sprite,
                body, 1);
    set.add_sprite(tail_sprite, model_.snake_.back());
}

void UI::draw_pause(ge211::Sprite_set &set) {
    draw_gameplay(set);
    set.add_sprite(iron_curtain, {0,0}, 1000);
}

void UI::draw_levelup(ge211::Sprite_set &set) {
    set.add_sprite(level_up_sprite,
            {model_.geometry_.mid_x() - 200,
             model_.geometry_.mid_y() - 150}, 1);
    //todo: figure out how to display numbers
}

ge211::Dimensions UI::initial_window_dimensions() const {
    return model_.window_dims();
}

std::string UI::initial_window_title() const {
    return "FANCY SNAKE";
}

ge211::Position UI::screen_to_board(ge211::Position pos) {
    return {pos.x / grid_dim.width, pos.y / grid_dim.height};
}

ge211::Position UI::board_to_screen(ge211::Position pos) {
    return {pos.x * grid_dim.width, pos.y * grid_dim.height};
}


