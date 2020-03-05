#include "model.hxx"

Model::Model(Geometry geometry)
: geometry_(geometry)
, apple_{-1,-1}
, score_(0)
, alive_(false)
, apple_timer_(5)
, snake_{{2, mid_y() + 1},{1, mid_y() + 1}}
, dir_{1,0}
, hole_top_ {mid_x(),0}
, hole_bottom_ {mid_x(), geometry_.board_dims_.height}
, hole_left_ {0, mid_y()}
, hole_right_ {geometry_.board_dims_.width, mid_y()}
{ }

// 1. move and stuff
// 2. check if the new position kills the snake/eats the apple
void Model::update() {

    snake_.push_front(snake_.front() + dir_);
    snake_.pop_back();


}

//

bool Model::good_pos(ge211::Position pos) {
    if (pos.x >= 0 && pos.x < geometry_.board_dims_.width
        && pos.y >= 0 && pos.y < geometry_.board_dims_.height)
        return true;
    //todo: holes, doors, obstacles etc.
}

