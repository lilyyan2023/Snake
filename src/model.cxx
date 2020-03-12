#include <utility>

#include "model.hxx"

Model::Model(Geometry geometry, int level)
: geometry_(geometry)
, apple_{-1, -1}
, score_(10)
, alive_(true)
, apple_timer_(4)
, snake_{{2, mid_y() + 1},{1, mid_y() + 1}}
, dir_{1,0}
, hole_top_ {mid_x() + 1,0}
, hole_bottom_ {mid_x() + 1, geometry_.board_dims_.height + 1}
, hole_left_ {0, mid_y() + 1}
, hole_right_ {geometry_.board_dims_.width + 1, mid_y() + 1}
, level_ {level} //more UI manipulation
, door_position_{-1,-1}
, skill_timer_ (0)
{
    for (int j = 0; j <= geometry_.board_dims_.height + 1; j++){
        if (j != mid_y() + 1){
            wall_positions_.emplace_back(0, j);
            wall_positions_.emplace_back(geometry_.board_dims_.width + 1, j);
        }
    }
    for (int i = 1; i <= geometry_.board_dims_.width; i++) {
        if (i != mid_x() + 1){
            wall_positions_.emplace_back(i, 0);
            wall_positions_.emplace_back(i, geometry_.board_dims_.height + 1);
        }
    }
}

// 1. move and stuff
// 2. check if the new position kills the snake/eats the apple
void Model::update() {
    turned_ = false;
    if (alive_ ) {
        snake_.push_front(snake_.front() + dir_);
        if (!eat_apple()){
            snake_.pop_back();
        }
        if (level_ != 3 && score_ >= Geometry::level_score(level_))
            open_door();
        turn_hole(snake_head());
        alive_ = good_pos(snake_head());
        if (snake_head() == snake_[snake_len() - 1]) {
            score_ -= 5;
            snake_.pop_back();
        }
    }
    interval_++;
    if (interval_ > geometry_.skill_interval_ * 2) {
        interval_ = 0;
    }
    // 0-interval can use the skill
    // interval-interval * 2 cannot use the skill
    // if using it between set interval_ back to 0

    if (state || skill_timer_ > 0) {
        skill_timer_ ++;
        geometry_.skill_factor_ = 2;
    }
    if (skill_timer_ > geometry_.skill_time_) {
        geometry_.skill_factor_ = 1;
        skill_timer_ = 0;
        interval_ = geometry_.skill_interval_ + 1;
        state = false;
    }
}
//1. check if the new position eats the apple
//2. increment the score based on the type of the apple the snake eats
//3. change the body color of the snake
bool Model::eat_apple() {
    bool eat = false;
    if (snake_head() == apple_) {
        eat = true;
        apple_ = {-1, -1};
        if (apple_timer_ <= 0) {
            score_ += geometry_.timed_apple_score_ + apple_timer_ + 5;
            apple_timer_ = 5;
        } else {
            score_ += geometry_.apple_score_ + 5;
        }
        apple_timer_--;
    } else if (apple_timer_ <= 0) {
        apple_timer_--;
        if (apple_timer_ <= -1 * geometry_.timed_apple_score_ + 5) {
            apple_timer_ = 4;
            apple_ = {-1, -1};
        }
    }
    return eat;
}
//

bool Model::good_pos(const ge211::Position& pos) const {
    for (ge211::Position w: wall_positions_) {
        if (pos == w) {
            return false;
        }
    }
    for (ge211::Position o: obstacle_positions_) {
        if (pos == o) {
            return false;
        }
    }
    for (int i = 1; i < snake_len() - 1; ++i) {
        if (pos == snake_[i]){
            return false;
        }
    }
    return true;
}
void Model::turn_hole(ge211::Position pos) {
    if (pos == hole_bottom_ + ge211::Dimensions{0,2}) {
        snake_.front() = hole_top_;
    }
    if (pos == hole_top_ + ge211::Dimensions{0,-1}) {
        snake_.front() = hole_bottom_;
    }
    if (pos == hole_left_ + ge211::Dimensions{-1, 0}) {
        snake_.front() = hole_right_;
    }
    if (pos == hole_right_ + ge211::Dimensions{2,0}) {
        snake_.front() = hole_left_;
    }
}

void Model::use_skill() {
    state = true;
}

void Model::open_door() {
    if (door_position_ != ge211::Position{-1,-1})
        return;
    door_position_ = {board_dims().width, board_dims().height + 1};
    for (auto &wall : wall_positions_)
        if (wall == door_position_) {
            std::swap(wall, wall_positions_.back());
            wall_positions_.pop_back();
        }
    wall_positions_.push_back(door_position_ + ge211::Dimensions{-1,1});
    wall_positions_.push_back(door_position_ + ge211::Dimensions{1,1});
    wall_positions_.push_back(door_position_ + ge211::Dimensions{-1,2});
    wall_positions_.push_back(door_position_ + ge211::Dimensions{1,2});
    door_position_ += ge211::Dimensions{0, 2};
}

void Model::set_obstacle(ge211::Position pos) {
    obstacle_positions_.push_back(pos);
}

