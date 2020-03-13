#pragma once

#include "geometry.hxx"
#include "RingBuffer.hxx"

class Model {
public:
    explicit Model(const Geometry&, int level);

    ge211::Dimensions window_dims() const { return geometry_.window_dims_; }
    ge211::Dimensions board_dims() const { return geometry_.board_dims_; }
    const ge211::Position& apple() { return apple_; }
    int level() const { return level_; }
    const Snake& snake() { return snake_; }
    int score() const { return score_; }
    int snake_len() const { return snake_.size(); }
    ge211::Position snake_head() const { return snake_.front(); }
    ge211::Position snake_tail() const { return snake_.back(); }
    bool alive() const { return alive_; }
    bool skill_available() const { return interval_ < geometry_.skill_interval_; }
    const std::vector<ge211::Position>& wall_positions()
    { return wall_positions_; }
    const std::vector<ge211::Position>& obstacle_positions()
    { return obstacle_positions_; }
    int apple_timer() const { return apple_timer_; }

    bool good_pos(const ge211::Position&) const;
    int mid_x() const { return geometry_.board_dims_.width / 2; }
    int mid_y() const { return geometry_.board_dims_.height / 2; }

    void set_snake(Snake& snk) { snake_ = snk; }
    void set_apple(ge211::Position pos) { apple_ = pos;}
    void turn(ge211::Dimensions dir);
    const Geometry& geometry() { return geometry_; }
    void use_skill() { state = true; }
    void update();
    void turn_hole(ge211::Position pos);
    void open_door();
    bool out_of_door() { return snake_head() == door_position_; }
    void set_obstacle(const ge211::Position&);
    bool using_skill() {return skill_timer_ > 0;}
    void set_dir(ge211::Dimensions d){ dir_ = d;}
private:
    bool eat_apple();
    int interval_ = 0;

    Geometry geometry_; // Dimensions of the board.
    ge211::Position apple_; // Position of apple, regular or timed.
    ge211::Dimensions dir_; // Direction of snake_.
    ge211::Position hole_top_; //top door
    ge211::Position hole_bottom_; //bottom door
    ge211::Position hole_left_; //left door
    ge211::Position hole_right_; //right door
    ge211::Position door_position_;

    std::vector<ge211::Position> obstacle_positions_; //Positions of obstacles
    std::vector<ge211::Position> wall_positions_; //Positions of walls
    int score_; //score varies between levels
    bool alive_; // Whether the snake is moving.

    // Starts at 5 and decreases each time. When reaches 0, timed apple appears,
    // apple_timer continues to decrease every round to calculate time penalty.
    // After timed apple is eaten/has disappeared, reset apple_timer to 5.
    int apple_timer_;
    bool turned_ = false;

    // The snake, stored as a ring buffer. ge211::Positions are default
    // initialized to {-1,-1}.
    Snake snake_;

    int level_; //each level corresponds to each number
    int skill_timer_; //record the amount of time skill is implemented
    bool state = false; //whether the game state is activated.
};


