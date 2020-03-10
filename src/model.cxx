#include "model.hxx"

Model::Model(Geometry geometry)
: geometry_(geometry)
, apple_{-1,-1}
, score_(10)
, alive_(true)
, apple_timer_(5)
, snake_{{2, mid_y() + 1},{1, mid_y() + 1}}
, dir_{1,0}
, hole_top_ {mid_x(),0}
, hole_bottom_ {mid_x(), geometry_.board_dims_.height}
, hole_left_ {0, mid_y()}
, hole_right_ {geometry_.board_dims_.width, mid_y()}
, door_ {geometry_.board_dims_.width, geometry_.board_dims_.height}
, level_ (1) //more UI manipulation
{ }

// 1. move and stuff
// 2. check if the new position kills the snake/eats the apple
void Model::update() {
    if (alive_ ) {
        snake_.push_front(snake_.front() + dir_);
        // TODO: checking the head's status is enough. You can try the "good_pos" func I wrote, might make it easier.
        // TODO: call eat_apple() somewhere in update
        for (ge211::Position s: snake_) {
            for (ge211::Position w: wall_positions) {
                if (s == w) {
                    alive_ = false;
                    return;
                }
            }
        }
        for (ge211::Position s: snake_) {
            for (ge211::Position o: obstacle_positions) {
                if (s == o) {
                    alive_ = false;
                    return;
                }
            }
        }
        if (snake_head() == snake_tail()) {
            snake_.pop_back();
        }
        for (int i = 1; i < snake_len() - 2; ++i) {
            if (snake_head() == snake_[i]){
                alive_ = false;
                return;
            }
        }
        eat_apple();
        if (eat_apple() == false){
            snake_.pop_back();
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
            apple_ = {0, 0};
            // TODO: this is the wrong grid to push.
            snake_.push_back(snake_tail() + dir_);
            if (apple_timer_ <= 0) {
                score_ = score_ + 5 + (1/abs(apple_timer_)) * 10 ;
                apple_timer_ = 5;
            } else {
                score_ = score_ + 6;
            }
        }
        if (score_ >= geometry_.level_score_[level_]){
            return eat;
        }
}
//

bool Model::good_pos(ge211::Position pos) {
    if (pos.x <= 0 || pos.x > geometry_.board_dims_.width
        || pos.y <= 0 || pos.y > geometry_.board_dims_.height)
        return false;
    //todo: holes, doors, obstacles etc.
}

