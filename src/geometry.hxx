#include <ge211.hxx>

#ifndef FINAL_PROJECT_GEOMETRY_HXX
#define FINAL_PROJECT_GEOMETRY_HXX

class Geometry {
public:
    friend class Model;
    friend class UI;
    Geometry()
    {
        window_dims_ = {(board_dims_.width + 2) * (grid_size + space_size)
            , (board_dims_.height + 2) * (grid_size + space_size) + 60};
    }

    int mid_x() { return window_dims_.width / 2; }
    int mid_y() { return window_dims_.height / 2; }
private:
    ge211::Dimensions board_dims_{41, 27}; // Dimension of the board
    ge211::Dimensions window_dims_;
    double update_interval_{0.07};
    int pass_score{400};
    int grid_size{20};
    int space_size{2};
};

#endif