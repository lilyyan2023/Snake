#ifndef FINAL_PROJECT_UI_HXX
#define FINAL_PROJECT_UI_HXX

#include "model.hxx"

const int grid_size = 36;
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
    ge211::Color get_color(int score); // Change color based on score.
    void draw_begin(ge211::Sprite_set&); // draw the begin menu
    void draw_gameplay(ge211::Sprite_set&);
    void draw_pause(ge211::Sprite_set&);
    void draw_levelup(ge211::Sprite_set&);

    Model model_;
    Screen status_; // Which screen do we display?

    ge211::Dimensions grid_dim{grid_size, grid_size}; // Helper for:
    // A grid of body.
    ge211::Rectangle_sprite body_sprite{grid_dim, get_color(model_.get_score())};
    ge211::Text_sprite title_sprite{"FANCY SNAKE", {"sans.ttf", 55}};
    ge211::Text_sprite press_key_sprite{"press any key to start", {"sans.ttf", 25}};

    // This is for pause interface.
    ge211::Rectangle_sprite iron_curtain{model_.window_dims(),
                                         ge211::Color::from_rgba(0.1, 0.4, 0.1, 0.3)};

    // Because a frame is too quick, we can use a timer to help update
    // the board once in every reasonable time period.
    double since_last_update;
};


#endif //FINAL_PROJECT_UI_HXX
