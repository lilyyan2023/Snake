#ifndef FINAL_PROJECT_UI_HXX
#define FINAL_PROJECT_UI_HXX

#include "model.hxx"

enum Screen { gameplay, begin, pause, levelup, gameover }; // For displaying different screens in UI.

class UI : public ge211::Abstract_game {
public:
    explicit UI(const Geometry&); // Initialize game with given dimensions.

protected:
    void draw(ge211::Sprite_set& set) override {
        switch (status_) {
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
            case gameover:
                draw_gameover(set);
                break;
        }
    }
    void on_key(ge211::Key) override; // Change direction with direction key.
    void on_frame(double) override; // Update if it's necessary.
    void on_mouse_down(ge211::Mouse_button, ge211::Position) override;

    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    /// Helpers
    Geometry geometry() { return model_.geometry(); }
    ge211::Color get_color(); // Change color based on score.
    void draw_begin(ge211::Sprite_set&); // draw the begin menu
    void draw_gameplay(ge211::Sprite_set&);
    void draw_pause(ge211::Sprite_set&);
    void draw_levelup(ge211::Sprite_set&);
    void draw_gameover(ge211::Sprite_set&);
    void update_sprites();
    ge211::Position screen_to_board(ge211::Position);
    ge211::Position board_to_screen(ge211::Position);
    bool can_put(const ge211::Position&);
    ge211::Position random_pos();

    ge211::Dimensions grid_dim;
    /// Sprites
    ge211::Rectangle_sprite wall_sprite{grid_dim, ge211::Color::white()};
    ge211::Circle_sprite apple_sprite{grid_dim.width / 2, ge211::Color::medium_red()};
    ge211::Rectangle_sprite body_sprite_{grid_dim, ge211::Color::white()};
    ge211::Rectangle_sprite tail_sprite{grid_dim, ge211::Color::medium_red()};
    ge211::Text_sprite title_sprite{"FANCY SNAKE", {"sans.ttf", 55}};
    ge211::Text_sprite press_key_sprite{"press any key to start", {"sans.ttf", 25}};
    ge211::Text_sprite pause_sprite{"PAUSE", {"sans.ttf", 55}};
    ge211::Text_sprite level_up_sprite{"Level up!", {"sans.ttf", 55}};
    ge211::Text_sprite game_over_sprite{"GAME OVER", {"sans.ttf", 55}};
    ge211::Text_sprite score_sprite_1{"score: 10", {"sans.ttf", 17}};
    ge211::Text_sprite score_sprite_2{"next level: 500", {"sans.ttf", 17}};
    // Counting down when leveling up
    int count_down_{3};
    void count_down()
    {
        if (!count_down_) {
            status_ = gameplay;
            model_.level_up();
            count_down_ = 3;
        }
        count_down_--;
    }
    // Drawing that countdown
    ge211::Text_sprite count_down_sprite_;
    ge211::Text_sprite &count_down_sprite()
    {
        count_down_sprite_ = {std::to_string(count_down_),
                              {"sans.ttf", 50}};
        return count_down_sprite_;
    }

    // This is for pause interface.
    ge211::Rectangle_sprite iron_curtain;
    ge211::Rectangle_sprite steel_curtain;

    Model model_;
    Screen status_; // Which screen do we display?

    // Because a frame is too quick, we can use a timer to help update
    // the board once in every reasonable time period.
    double since_last_update;
};


#endif //FINAL_PROJECT_UI_HXX
