#include "ui.hxx"

UI::UI(const Geometry& geometry, int lev)
: model_{geometry, lev}
, grid_dim{geometry.grid_size, geometry.grid_size}
, status_(begin)
, since_last_update(0)
, iron_curtain{geometry.window_dims_,
               ge211::Color::from_rgba(0.1, 0.4, 0.1, 0.3)}
, steel_curtain{geometry.window_dims_,
                ge211::Color::from_rgba(0.4, 0.1, 0.1, 0.3)}
{
    set_obstacles();
    score_sprite_1 = ge211::Text_sprite
            {"score: " + std::to_string(model_.score())
             , {"sans.ttf", 17}};
    score_sprite_2 = ge211::Text_sprite
            {"next level: " + std::to_string(Geometry::level_score(level()))
                    , {"sans.ttf", 17}};
}

void UI::on_key(ge211::Key key) {
    switch (status_) {
        case begin:
        case pause:
            status_ = gameplay;
            break;
        case gameover:
            if (key == ge211::Key::code('b')) {
                model_ = Model(geometry(), level());
                set_obstacles();
                status_ = gameplay;
            }
            break;
        case gameplay:
            if (key == ge211::Key::code('q'))
                status_ = pause;
            if (key == ge211::Key::up())
                model_.turn({0, -1});
            if (key == ge211::Key::down())
                model_.turn({0, 1});
            if (key == ge211::Key::left())
                model_.turn({-1, 0});
            if (key == ge211::Key::right())
                model_.turn({1, 0});
            if (key == ge211::Key::code(' ') && model_.skill_available())
                model_.use_skill();
            break;
        case levelup:
            if (key == ge211::Key::code('b')) {
                model_ = Model(geometry(), level());
                set_obstacles();
                status_ = gameplay;
            }
            if (key == ge211::Key::code('n')) {
                model_ = Model(geometry(), level() + 1);
                set_obstacles();
                status_ = countdown;
            }
            break;
        default:
            break;
    }
}

void UI::on_mouse_down(ge211::Mouse_button, ge211::Position) {
    if (status_ == begin || status_ == pause)
        status_ = gameplay;
}

void UI::on_frame(double elapsed) {
    switch (status_) {
        case gameplay:
            since_last_update += elapsed;
            if (since_last_update >= geometry().update_interval(level())) {
                since_last_update = 0;
                model_.update();
                update_sprites();
                if (!model_.alive())
                    status_ = gameover;
                if (model_.apple() == ge211::Position{-1,-1})
                    model_.set_apple(random_pos());
                if (model_.out_of_door())
                    status_ = levelup;
            }
            break;
        case countdown:
            since_last_update += elapsed;
            if (since_last_update >= 1) {
                since_last_update = 0;
                count_down();
            }
            break;
        default:
            break;
    }
}

ge211::Color UI::get_color() {
    if (model_.score() < Geometry::level_score(level()) / 6)
        return ge211::Color::white();
    if (model_.score() < Geometry::level_score(level()) / 6 * 2)
        return ge211::Color::medium_yellow();
    if (model_.score() < Geometry::level_score(level()) / 6 * 3)
        return ge211::Color::medium_green();
    if (model_.score() < Geometry::level_score(level()) / 6 * 4)
        return ge211::Color::medium_blue();
    if (model_.score() < Geometry::level_score(level()) / 6 * 5)
        return ge211::Color::medium_red();
    return ge211::Color::medium_magenta();
}

void UI::draw_begin(ge211::Sprite_set &set) {
    set.add_sprite(title_sprite,
                   {geometry().mid_x() - 200,
                    geometry().mid_y() - 150}, 1);
    set.add_sprite(press_key_sprite,
                   {geometry().mid_x() - 130,
                    geometry().mid_y() + 160}, 1);
}

void UI::draw_gameplay(ge211::Sprite_set &set) {
    for (auto wall : model_.wall_positions())
        set.add_sprite(wall_sprite, board_to_screen(wall), 0);
    for (auto o : model_.obstacle_positions())
        set.add_sprite(obstacle_sprite_, board_to_screen(o), 0);
    for (auto body : model_.snake()) {
        if (body == model_.snake().back())
            set.add_sprite(tail_sprite,
                    board_to_screen(body), 2);
        else
            set.add_sprite(body_sprite_,
                           board_to_screen(body), 1);
    }
    set.add_sprite(score_sprite_1,
            {2, window_dims().height - 48}, 2);
    set.add_sprite(score_sprite_2,
                   {2, window_dims().height - 28}, 2);
    set.add_sprite(apple_sprite(), board_to_screen(model_.apple())
            - apple_sprite_.dimensions() / 2 + grid_dim / 2, 0);
    if (model_.skill_available() || model_.using_skill()) {
        if (model_.using_skill())
            set.add_sprite(using_background_sprite,
                       {geometry().mid_x(),
                        window_dims().height - 38}, 1);
        else
            set.add_sprite(ready_background_sprite,
                          {geometry().mid_x(),
                           window_dims().height - 38}, 1);
        set.add_sprite(skill_ready_sprite,
                       {geometry().mid_x(),
                        window_dims().height - 48}, 2);
    }
}

void UI::draw_pause(ge211::Sprite_set &set) {
    draw_gameplay(set);
    set.add_sprite(iron_curtain, {0,0}, 10);
    set.add_sprite(pause_sprite, {geometry().mid_x() - 100,
                                  geometry().mid_y() - 150}, 11);
}

void UI::draw_countdown(ge211::Sprite_set &set) {
    set.add_sprite(level_up_sprite,
            {geometry().mid_x() - 110,
             geometry().mid_y() - 150}, 1);
    set.add_sprite(count_down_sprite(),
                   {geometry().mid_x() - 20,
                    geometry().mid_y() + 150}, 1);
}

void UI::draw_gameover(ge211::Sprite_set &set) {
    draw_gameplay(set);
    set.add_sprite(steel_curtain, {0,0}, 10);
    set.add_sprite(game_over_sprite,
            {geometry().mid_x() - 175,
             geometry().mid_y() - 150}, 11);
    set.add_sprite(restart_sprite,
                   {geometry().mid_x() - 110,
                    geometry().mid_y() + 160}, 11);
}

void UI::draw_levelup(ge211::Sprite_set &set) {
    draw_gameplay(set);
    set.add_sprite(iron_curtain, {0,0}, 10);
    set.add_sprite(level_up_sprite,
                   {geometry().mid_x() - 110,
                    geometry().mid_y() - 150}, 11);
    set.add_sprite(restart_sprite,
                   {geometry().mid_x() - 110,
                    geometry().mid_y() + 160}, 11);
    set.add_sprite(advance_sprite,
                   {geometry().mid_x() - 120,
                    geometry().mid_y() + 200}, 11);
}

ge211::Dimensions UI::initial_window_dimensions() const {
    return model_.window_dims();
}

std::string UI::initial_window_title() const {
    return "FANCY SNAKE";
}

ge211::Position UI::screen_to_board(ge211::Position pos) {
    return {pos.x / (grid_dim.width + geometry().space_size)
            , pos.y / (grid_dim.height + geometry().space_size)};
}

ge211::Position UI::board_to_screen(ge211::Position pos) {
    return {pos.x * (grid_dim.width + geometry().space_size)
            , pos.y * (grid_dim.height + geometry().space_size)};
}

void UI::update_sprites() {
    body_sprite_ = ge211::Rectangle_sprite
            {grid_dim, get_color()};
    score_sprite_1 = ge211::Text_sprite
            {"score: " + std::to_string(model_.score())
             , {"sans.ttf", 17}};
    if (level() != 3)
        score_sprite_2 = ge211::Text_sprite
            {"next level: " + std::to_string(Geometry::level_score(level()))
                    , {"sans.ttf", 17}};
    else
        score_sprite_2 = ge211::Text_sprite
                {"next level: N/A"
                        , {"sans.ttf", 17}};
}

bool UI::can_put(const ge211::Position& pos) {
    if (pos == model_.snake_head() || pos == model_.snake_tail()
    || pos == model_.apple())
        return false;
    return model_.good_pos(pos);
}

ge211::Position UI::random_pos() {
    ge211::Position pos{-1,-1};
    do
        pos = {get_random().between(1, board_dims().width),
               get_random().between(1, board_dims().height)};
    while (!can_put(pos));
    return pos;
}

void UI::set_obstacles() {
    for (int i = 0; i < Geometry::obstacle_number(level()); i++)
        model_.set_obstacle(random_pos());
}

