#include "model.hxx"
#include <catch.hxx>


TEST_CASE("initial location of the snake_")
{
    Geometry geometry;
    Model m(geometry);
    CHECK( m.snake_head() == ge211::Position{2, 14} );
    CHECK( m.snake_len() == 2);
}
TEST_CASE("dead when snake_ collides with the edge")
{
    Geometry geometry;
    Model m(geometry);
    Snake snk = {
            ge211::Position{0, 0},
            ge211::Position{0, 1},
    };
    m.set_snake(snk);
    m.turn({0, -1});
    CHECK( m.alive() == true);
    m.update();
    CHECK( !m.alive() == false);
}
TEST_CASE("snake_'s length cut off")
{
    Geometry geometry;
    Model m(geometry);
    Snake snk = {
            ge211::Position{1, 5},
            ge211::Position{1, 4},
            ge211::Position{1, 3},
            ge211::Position{1, 2},
            ge211::Position{1, 1},
    };
    m.set_snake(snk);
    m.turn({1, 0});
    m.update();
    m.turn({0,-1});
    m.update();
    m.turn({-1,0});
//    m.turn({0,-1});
    CHECK( m.snake_len() == 5 );
    m.update();
    CHECK( m.snake_len() == 4 );
}
TEST_CASE("dead when snake_ collides with its other body parts")
{
    Geometry geometry;
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
    CHECK( m.alive() == true);
    m.update();
    CHECK( m.alive() == false);
}
TEST_CASE("grows when eat an apple")
{
    Geometry geometry;
    Model m(geometry);
    Snake snk = {
            ge211::Position{1, 3},
            ge211::Position{1, 2},
            ge211::Position{1, 1},
    };
    m.set_snake(snk);
    m.turn({0, 1});
    m.set_apple({1, 4});

    CHECK( m.snake_len() == 3 );
    m.update();
    CHECK( m.snake_len() == 4);
}
