#include "model.hxx"
#include <catch.hxx>

const ge211::Dimensions board_dim{36, 36};

TEST_CASE("initial location of the snake_")
{
    Geometry geometry(board_dim);
    Model m(geometry);
    CHECK( m.snake_head() == ge211::Position{grid_size / 2, 0} );
    CHECK( m.snake_len() == 1 );
}
TEST_CASE("dead when snake_ collides with the edge")
{
    Geometry geometry(board_dim);
    Model m(geometry);
    Snake snk = {
            ge211::Position{0, 0},
            ge211::Position{0, 1},
    };
    m.set_snake(snk);
    m.turn({0, -1});
    CHECK( m.isalive() );
    m.update();
    CHECK( !m.isalive() );
}
TEST_CASE("snake_'s length cut off")
{
    Geometry geometry(board_dim);
    Model m(geometry);
    Snake snk = {
            ge211::Position{0, 0},
            ge211::Position{0, 1},
            ge211::Position{0, 2},
            ge211::Position{1, 2},
            ge211::Position{1, 1},
    };
    m.set_snake(snk);
    m.turn({-1, 0});
    CHECK( m.snake_len() == 4 );
    m.update();
    CHECK( m.snake_len() == 3 );
}
TEST_CASE("dead when snake_ collides with its other body parts")
{
    Geometry geometry(board_dim);
    Model m(geometry);
    Snake snk = {
            ge211::Position{0, 0},
            ge211::Position{0, 1},
            ge211::Position{0, 2},
            ge211::Position{0, 3},
            ge211::Position{1, 3},
            ge211::Position{1, 2},
    };
    m.set_snake(snk);
    m.turn({-1, 0});
    CHECK( m.isalive() );
    m.update();
    CHECK( !m.isalive() );
}
TEST_CASE("grows when eat an apple")
{
    Geometry geometry(board_dim);
    Model m(geometry);
    Snake snk = {
            ge211::Position{0, 0},
            ge211::Position{0, 1},
            ge211::Position{0, 2},
    };
    m.set_snake(snk);
    m.turn({0, 1});
    m.set_apple({0, 3});

    CHECK( m.snake_len() == 3 );
    m.update();
    CHECK( m.snake_len() == 4);
}
