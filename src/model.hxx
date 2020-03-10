#pragma once

#include "geometry.hxx"
#include "RingBuffer.hxx"

class Model {
public:
    //friend class UI;
    explicit Model(Geometry );

    // Turn the snake_ to another direction.
    void turn(ge211::Dimensions dir) {
        if (dir_ + dir != ge211::Dimensions {0,0})
            dir_ = dir;
    }
    // Advances the snake_, check if dies. Eats apple and grow if possible.
    void update();
    void turn_hole(ge211::Position pos);
    // helpers
    int mid_x() const { return geometry_.board_dims_.width / 2; }
    int mid_y() const { return geometry_.board_dims_.height / 2; }
    ge211::Dimensions window_dims() const { return geometry_.window_dims_; }
    ge211::Dimensions board_dims() const { return geometry_.board_dims_; }
    bool good_pos(const ge211::Position&); // Check if OOB, hits obstacle, hits wall, hits self.

    // Helpers
    void level_up();
    void set_snake(Snake& snk) { snake_ = snk; }
    ge211::Position apple() { return apple_; }
    void set_apple(const ge211::Position& pos) { apple_ = pos; }
    void set_holes()
    {
        hole_top_ = {mid_x(),0};
        hole_bottom_ = {mid_x(), geometry_.board_dims_.height};
        hole_left_ = {0, mid_y()};
        hole_right_ = {geometry_.board_dims_.width, mid_y()};
    }
    int level() { return level_; }
    Snake& snake() { return snake_; }
    Geometry &geometry() { return geometry_; }
    bool alive() const { return alive_; }
    int score() const { return score_; }
    int snake_len() const { return snake_.size(); }
    ge211::Position snake_head() const { return snake_.front(); }
    ge211::Position snake_tail() const { return snake_.back(); }
    std::vector<ge211::Position>& wall_positions() { return wall_positions_; }
    std::vector<ge211::Position>& obstacle_positions() { return obstacle_positions_; }

private:
    bool eat_apple();

    Geometry geometry_; // Dimensions of the board.
    ge211::Position apple_; // Position of apple, regular or timed.
    ge211::Dimensions dir_; // Direction of snake_.
    ge211::Position hole_top_; //top door
    ge211::Position hole_bottom_; //bottom door
    ge211::Position hole_left_; //left door
    ge211::Position hole_right_; //right door

    std::vector<ge211::Position> obstacle_positions_; //Positions of obstacles
    std::vector<ge211::Position> wall_positions_; //Positions of walls
    int score_; //score varies between levels
    bool alive_; // Whether the snake is moving.

    // Starts at 5 and decreases each time. When reaches 0, timed apple appears,
    // apple_timer continues to decrease every round to calculate time penalty.
    // After timed apple is eaten/has disappeared, reset apple_timer to 5.
    int apple_timer_;

    // The snake, stored as a ring buffer. ge211::Positions are default
    // initialized to {-1,-1}.
    Snake snake_;

    int level_; //each level corresponds to each number
};


