#ifndef FINAL_PROJECT_UI_HXX
#define FINAL_PROJECT_UI_HXX

#include "model.hxx"

enum Screen { gameplay, begin, pause, levelup }; // For displaying different screens in UI.


class UI : public ge211::Abstract_game {
public:
    explicit UI(Geometry); // Initialize game with given dimensions.

protected:
    void draw(ge211::Sprite_set&) override; // Draw it.
    void on_key(ge211::Key) override; // Change direction with direction key.
    void on_frame(double) override; // Update if it's necessary.

    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    /// Helpers
    ge211::Color get_color(int score); // Change color based on score.
    void draw_begin(ge211::Sprite_set&); // draw the begin menu
    void draw_gameplay(ge211::Sprite_set&);
    void draw_pause(ge211::Sprite_set&);
    void draw_levelup(ge211::Sprite_set&);
    ge211::Position screen_to_board(ge211::Position);
    ge211::Position board_to_screen(ge211::Position);

    ge211::Dimensions grid_dim{model_.geometry_.grid_size
                               , model_.geometry_.grid_size}; // Helper for:
    // A grid of body.
    ge211::Rectangle_sprite body_sprite{grid_dim, get_color(model_.get_score())};
    ge211::Rectangle_sprite tail_sprite{grid_dim, ge211::Color::medium_red()};
    ge211::Text_sprite title_sprite{"FANCY SNAKE", {"sans.ttf", 55}};
    ge211::Text_sprite press_key_sprite{"press any key to start", {"sans.ttf", 25}};
    ge211::Text_sprite number_sprite{};
    ge211::Text_sprite level_up_sprite{"Level up!", {"sans.ttf", 55}};

    // This is for pause interface.
    ge211::Rectangle_sprite iron_curtain{model_.window_dims(),
                                         ge211::Color::from_rgba(0.1, 0.4, 0.1, 0.3)};

    Model model_;
    Screen status_; // Which screen do we display?

    // Because a frame is too quick, we can use a timer to help update
    // the board once in every reasonable time period.
    double since_last_update;

    // countdown before levelup.
    int level_up_count_{3};
    void level_up_count() {
        if (!level_up_count_) {
            status_ = gameplay;
            level_up_count_ = 3;
        }
        level_up_count_--;
    }

    int level = 1; //current level form 1 to 3.
};


#endif //FINAL_PROJECT_UI_HXX
