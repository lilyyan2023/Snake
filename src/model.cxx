#include <utility>

#include "model.hxx"

Model::Model(Geometry  geometry)
: geometry_(std::move(geometry))
, apple_{-1, -1}
, score_(10)
, alive_(true)
, apple_timer_(5)
, snake_{{2, mid_y() + 1},{1, mid_y() + 1}}
, dir_{1,0}
, hole_top_ {mid_x() + 1,0}
, hole_bottom_ {mid_x() + 1, geometry_.board_dims_.height}
, hole_left_ {0, mid_y() + 1}
, hole_right_ {geometry_.board_dims_.width, mid_y() + 1}
, level_ (1)
, skill_timer_ (0)
{
    // TODO; holes!
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
        turn_hole(snake_head());
        alive_ = good_pos(snake_head());
        if (snake_head() == snake_[snake_len() - 1])
            snake_.pop_back();
    }
    interval_++;
    // 0-interval can use the skill
    // interval-interval * 2 cannot use the skill
    // if using it between set interval_ back to 0

    if (interval_ > geometry_.skill_interval_ * 2){
        interval_ = 0;
    }
    if (state == true){
        skill_timer_ ++;
    }
    if (skill_timer_ > 0){
        skill_timer_ ++;
    }
    if (interval_ > geometry_.skill_interval_ && interval_ < geometry_.skill_interval_ * 2){
        state = false;
    }
    if (skill_timer_ > geometry_.skill_time_ ){
        geometry_.update_interval_ /= 2;
        skill_timer_ = 0;
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
            score_ += geometry_.timed_apple_score_ + apple_timer_;
            apple_timer_ = geometry_.apple_score_;
        } else {
            score_ += geometry_.apple_score_;
        }
        apple_timer_--;
    } else if (apple_timer_ <= 0) {
        apple_timer_--;
        if (apple_timer_ <= -1 * geometry_.timed_apple_score_) {
            apple_timer_ = geometry_.apple_score_;
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
    //TODO: hits wall, obstacles, or self.
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

void Model::level_up() {
    level_++;
    geometry_.update_interval_ -= 0.025;
}

void Model::use_skill(bool state_, int round) {
    this->state = state_;

     if (state && skill_timer_ < geometry_.skill_time_){
         geometry_.update_interval_ = geometry_.update_interval_*2;
     }
}

