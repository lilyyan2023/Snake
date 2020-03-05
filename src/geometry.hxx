

// This is for calibrating parameters quickly. Might add more.
#include <ge211.hxx>

#ifndef FINAL_PROJECT_GEOMETRY_HXX
#define FINAL_PROJECT_GEOMETRY_HXX

class Geometry {
public:
    friend class Model;
    Geometry() = default;

    int mid_x() { return window_dims_.width / 2; }
    int mid_y() { return window_dims_.height / 2; }
private:
    ge211::Dimensions board_dims_{16, 16}; // Dimension of the board
    ge211::Dimensions window_dims_{1024, 768};
    double update_interval_{0.25};
    int pass_score{400};
};

#endif