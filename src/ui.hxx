//
// Created by Anxin Guo on 2/29/20.
//

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

private:
    ge211::Color get_color(int score); // Change color based on score.

    Model model_;
    Screen status_; // Which screen do we display?

    ge211::Dimensions grid_dim{grid_size, grid_size}; // Helper for:
    // A grid of body.
    ge211::Rectangle_sprite body_sprite{grid_dim, get_color(model_.get_score())};

    // Because a frame is too quick, we can use a timer to help update
    // the board once in every reasonable time period.
    double since_last_update;
};


#endif //FINAL_PROJECT_UI_HXX
