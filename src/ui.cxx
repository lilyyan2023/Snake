#include "ui.hxx"

UI::UI(Geometry geometry)
: model_(geometry)
, grid_dim{geometry.grid_size, geometry.grid_size}
, status_(Screen::begin)
, since_last_update(0)
, iron_curtain{geometry.window_dims_,
               ge211::Color::from_rgba(0.1, 0.4, 0.1, 0.3)}
{ }

void UI::on_key(ge211::Key key) {
    if (status_ == begin || status_ == pause)
        status_ = gameplay;
    else if (status_ == gameplay && key == ge211::Key::code('q'))
        status_ = pause;
    //todo: other scenarios
}

void UI::on_mouse_down(ge211::Mouse_button, ge211::Position) {
    if (status_ == begin || status_ == pause)
        status_ = gameplay;
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
            if (since_last_update >= 1) {
                since_last_update = 0;
                // 3 seconds
                count_down();
            }
            break;
        default:
            break;
    }
}

ge211::Color UI::get_color(int score) {
    //todo: change color based on score.
    return ge211::Color::white();
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
    for (auto body : model_.snake_) {
        if (body == model_.snake_.back())
            set.add_sprite(tail_sprite,
                    board_to_screen(body), 2);
        else
            set.add_sprite(body_sprite,
                    board_to_screen(body), 1);
    }
}

void UI::draw_pause(ge211::Sprite_set &set) {
    draw_gameplay(set);
    set.add_sprite(iron_curtain, {0,0}, 100);
    set.add_sprite(pause_sprite, {model_.geometry_.mid_x() - 100,
                                  model_.geometry_.mid_y() - 150}, 101);
}

void UI::draw_levelup(ge211::Sprite_set &set) {
    //todo: adjust coordinates
    set.add_sprite(level_up_sprite,
            {model_.geometry_.mid_x() - 120,
             model_.geometry_.mid_y() - 150}, 1);
    set.add_sprite(count_down_sprite(),
                   {model_.geometry_.mid_x() - 20,
                    model_.geometry_.mid_y() + 150}, 1);
}

ge211::Dimensions UI::initial_window_dimensions() const {
    return model_.window_dims();
}

std::string UI::initial_window_title() const {
    return "FANCY SNAKE";
}

ge211::Position UI::screen_to_board(ge211::Position pos) {
    return {pos.x / (grid_dim.width + model_.geometry_.space_size)
            , pos.y / (grid_dim.height + model_.geometry_.space_size)};
}

ge211::Position UI::board_to_screen(ge211::Position pos) {
    return {pos.x * (grid_dim.width + model_.geometry_.space_size)
            , pos.y * (grid_dim.height + model_.geometry_.space_size)};
}
