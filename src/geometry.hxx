#include <ge211.hxx>

#ifndef FINAL_PROJECT_GEOMETRY_HXX
#define FINAL_PROJECT_GEOMETRY_HXX

class Geometry {
public:
    friend class Model;
    friend class UI;
    explicit Geometry(int n = 41, int m = 27)
    {
        board_dims_ = ge211::Dimensions{n, m};
        window_dims_ = {(board_dims_.width + 2) * (grid_size + space_size)
            , (board_dims_.height + 2) * (grid_size + space_size) + 55};
    }
    Geometry(const Geometry& g)
    {
        *this = g;
        skill_factor_ = 1;
    }
    int mid_x() const { return window_dims_.width / 2; }
    int mid_y() const { return window_dims_.height / 2; }
    static int level_score(int n) { return 80 * n; }
    static int obstacle_number(int n) { return n * (n + 1) / 2; }
    double update_interval(int n) const { return (0.13 - n * 0.01) * skill_factor_; }
private:
    ge211::Dimensions board_dims_{41, 27}; // Dimension of the board
    ge211::Dimensions window_dims_{};
    int grid_size{20};
    int space_size{2};

    int apple_score_ = 5;
    int timed_apple_score_ = 40;
    int skill_interval_ = 80;
    int skill_time_ = 30;
    int skill_factor_ = 1;
};

#endif