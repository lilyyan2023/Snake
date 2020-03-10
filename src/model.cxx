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
, hole_top_ {mid_x(),0}
, hole_bottom_ {mid_x(), geometry_.board_dims_.height}
, hole_left_ {0, mid_y()}
, hole_right_ {geometry_.board_dims_.width, mid_y()}
, level_ (1) //more UI manipulation
{
    // TODO; holes!
        for (int j = 0; j <= geometry_.board_dims_.height + 1; j++){
            wall_positions_.emplace_back(0, j);
            wall_positions_.emplace_back(geometry_.board_dims_.width + 1, j);
        }
        for (int i = 1; i <= geometry_.board_dims_.width; i++) {
            wall_positions_.emplace_back(i, 0);
            wall_positions_.emplace_back(i, geometry_.board_dims_.height + 1);
        }
}

// 1. move and stuff
// 2. check if the new position kills the snake/eats the apple
void Model::update() {
    if (alive_ ) {
        snake_.push_front(snake_.front() + dir_);
        if (!eat_apple()){
            snake_.pop_back();
        }
        // TODO: do this in the "good_pos" function.
        for (ge211::Position s: snake_) {
            for (ge211::Position w: wall_positions_) {
                if (s == w) {
                    alive_ = false;
                    return;
                }
            }
        }
        for (ge211::Position s: snake_) {
            for (ge211::Position o: obstacle_positions_) {
                if (s == o) {
                    alive_ = false;
                    return;
                }
            }
        }
        if (snake_head() == snake_[snake_len() - 1]) {
            snake_.pop_back();
        }
        for (int i = 1; i < snake_len() - 2; ++i) {
            if (snake_head() == snake_[i]){
                alive_ = false;
                return;
            }
        }
    }
}
//1. check if the new position eats the apple
//2. increment the score based on the type of the apple the snake eats
//3. change the body color of the snake
bool Model::eat_apple() {
    bool eat = false;
    //level 1 : 120 (subject to change)
    // TODO: Can store the constants in geometry_ so it's easier to manage.
    // TODO: Then you don't have to separate the cases.
    if (snake_head() == apple_) {
        eat = true;
        apple_timer_--;
        apple_ = {-1, -1};
        if (apple_timer_ <= 0) {
            score_ = score_ + 5 + (1/abs(apple_timer_)) * 10 ;
            apple_timer_ = 5;
        } else {
            score_ = score_ + 6;
        }
    }

    return eat;
}
//

bool Model::good_pos(const ge211::Position& pos) {
    if (pos.x <= 0 || pos.x > geometry_.board_dims_.width
        || pos.y <= 0 || pos.y > geometry_.board_dims_.height)
        return false;
    //TODO: hits wall, obsticles, or self.
}

void Model::level_up() {
    // TODO: calibrate speed; choose to stay or continue.
    level_++;
    geometry_.update_interval_ -= 0.05;
}

