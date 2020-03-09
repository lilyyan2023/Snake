#include "model.hxx"

Model::Model(Geometry geometry)
: geometry_(geometry)
, apple_{-1,-1}
, score_(0)
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
        for (int i = 0; i < snake_len() - 2; ++i) {
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
void Model::eat_apple() {
    if (level_ == 1) {
        //level 1 : 120 (subject to change)
        while (score_ < 120) {
            int round = 1;
            int normal_apple = 0;
            int timed_apple = 0;
            score_ = snake_len() * 5 + normal_apple * 1 + timed_apple * 10;
            if (snake_head() == apple_) {
                snake_.push_back(snake_tail() + dir_);
                if (round % 5 != 0) {
                    normal_apple++;
                } else {
                    timed_apple++;
                }
                round++;
            }
            //change color per 20 points
        }

    }
    if (level_ == 2){
        //level 2 : 300 (subject to change)
        while (score_ < 300){
            int round = 1;
            int normal_apple = 0;
            int timed_apple = 0;
            score_ = snake_len() * 5 + normal_apple * 1 + timed_apple * 10;
            if (snake_head() == apple_){
                snake_.push_back(snake_tail() + dir_);
                if (round % 5 != 0){
                    normal_apple ++;
                }
                else{
                    timed_apple ++;
                }
                round++;
            }
        }
        //change color per 50 points
    }
    if (level_ == 3){
        //level 3 : 600 (subject to change)
        while (score_ < 600){
            int round = 1;
            int normal_apple = 0;
            int timed_apple = 0;
            score_ = snake_len() * 5 + normal_apple * 1 + timed_apple * 10;
            if (snake_head() == apple_){
                snake_.push_back(snake_tail() + dir_);
                if (round % 5 != 0){
                    normal_apple ++;
                }
                else{
                    timed_apple ++;
                }
                round++;
            }
        }
        //change color per 100 points
    }
}
//

bool Model::good_pos(ge211::Position pos) {
    if (pos.x >= 0 && pos.x < geometry_.board_dims_.width
        && pos.y >= 0 && pos.y < geometry_.board_dims_.height)
        return true;
    //todo: holes, doors, obstacles etc.
}

