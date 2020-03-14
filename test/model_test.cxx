#include "model.hxx"
#include <catch.hxx>


TEST_CASE("initial location of the snake_")
{
    Model m(Geometry(), 1);
    CHECK( m.snake_head() == ge211::Position{2, 14} );
    CHECK( m.snake_len() == 2);
}
TEST_CASE("dead when snake_ collides with the edge")
{
    Model m(Geometry(), 1);
    Snake snk = {
            ge211::Position{1, 1},
            ge211::Position{1, 2},
    };
    m.set_snake(snk);
    m.turn({0, -1});
    CHECK( m.alive() );
    m.update();
    CHECK( !m.alive() );
}
TEST_CASE("snake_'s length cut off")
{
    //favorite test 1
    Model m(Geometry(), 1);
    Snake snk =
            {{1, 5},
            {1, 4},
            {1, 3},
            {1, 2},
            {1, 1},};
    m.set_snake(snk);
    m.turn({1, 0});
    m.update();
    m.turn({0,-1});
    m.update();
    m.turn({-1,0});
    CHECK( m.snake_len() == 5 );
    m.update();
    CHECK( m.snake_len() == 4 );
    CHECK( m.alive() );
}
TEST_CASE("dead when snake_ collides with its other body parts")
{
    Model m(Geometry(), 1);
    Snake snk =
            {{3,2},
            {4,2},
            {4,1},
            {3,1},
            {2,1},
            {1,1}};
    m.set_snake(snk);
    m.turn({0, -1});
    CHECK( m.alive() );
    m.update();
    CHECK( !m.alive() );
}
TEST_CASE("grows when eat a normal apple")
{
    Model m(Geometry(), 1);
    Snake snk =
            {{1, 3},
            {1, 2},
            {1, 1}};
    m.set_snake(snk);
    m.turn({0, 1});
    m.set_apple({1, 4});

    CHECK( m.snake_len() == 3 );
    m.update();
    CHECK( m.snake_len() == 4);
}
TEST_CASE("score grows more when eat a timed apple")
{ //Test case 2
    Model m(Geometry(), 1);
    Snake snk =
            {{1, 3},
             {1, 2}};
    m.set_snake(snk);
    m.turn({0, 1});
    m.set_apple({1, 4});

    CHECK( m.snake_len() == 2 );
    m.update();
    CHECK( m.snake_len() == 3);
    CHECK( m.score() == m.snake_len() * 5 + 5);

    m.turn({1,0});
    m.set_apple({2,4});
    m.update();
    CHECK( m.snake_len() == 4);
    CHECK( m.score() == m.snake_len() * 5 + 5 * 2);

    m.turn({1,0});
    m.set_apple({3,4});
    m.update();
    CHECK( m.snake_len() == 5);
    CHECK( m.score() == m.snake_len() * 5 + 5 * 3);

    m.turn({0,-1});
    m.set_apple({3,3});
    m.update();
    CHECK( m.snake_len() == 6);
    CHECK( m.score() == m.snake_len() * 5 + 5 * 4);

    m.turn({0,-1});
    m.set_apple({3,2});
    m.update();
    CHECK( m.snake_len() == 7);
    CHECK( m.score() == m.snake_len() * 5 + 5 * 4 + 40);
}
TEST_CASE("dead when snake collides with obstacles")
{//TEST CASE 3
    Model m(Geometry(), 1);
    Snake snk =
            {{1, 3},
             {1, 2}};
    m.set_snake(snk);
    m.turn({0, 1});
    m.set_obstacle({1,4});
    m.update();
    CHECK( !m.alive() );
}
TEST_CASE("use the skill")
{//TEST CASE 4
    Model m(Geometry(), 3);
    m.use_skill();
    m.update();
    CHECK( m.geometry().update_interval(3) == 0.2);
}
TEST_CASE("get into top hole")
{//TEST CASE 5
    Model m(Geometry(), 3);
    Snake snk =
            {{21, 1},
             {21, 2}};
    m.set_snake(snk);
    m.turn({0, -1});
    m.update();
    m.update();
    CHECK( m.snake() == Snake{{21,28}, {21,0}});
}
TEST_CASE("get into bottom hole")
{
    Model m(Geometry(), 3);
    Snake snk =
            {{21, 27},
             {21, 26}};
    m.set_snake(snk);
    m.turn({0, 1});
    m.update();
    m.update();
    CHECK( m.snake() == Snake{{21,0}, {21,28}});
}
TEST_CASE("get into left hole")
{
    Model m(Geometry(), 3);
    Snake snk =
            {{1, m.mid_y()+1},
             {2, m.mid_y()+1}};
    m.set_snake(snk);
    m.set_dir({-1,0});
    m.update();
    m.update();
    CHECK( m.snake() == Snake{{42,m.mid_y()+1}, {0,m.mid_y()+1}});
}
TEST_CASE("get into right hole")
{
    Model m(Geometry(), 3);
    Snake snk =
            {{41, m.mid_y()+1},
             {40, m.mid_y()+1}};
    m.set_snake(snk);
    m.set_dir({1,0});
    m.update();
    m.update();
    CHECK( m.snake() == Snake{{0,m.mid_y()+1}, {42,m.mid_y()+1}});
}
TEST_CASE( "speed" )
{
    Model m1(Geometry(), 1);
    double interval = m1.geometry().update_interval(m1.level());
    m1.update();
    m1.update();
    CHECK( interval == m1.geometry().update_interval(m1.level()) );
    Model m2(m2.geometry(), 2);
    CHECK( interval > m2.geometry().update_interval(m2.level()) );
    interval = m2.geometry().update_interval(m2.level());
    m2.update();
    m2.update();
    m2.update();
    CHECK( interval == m2.geometry().update_interval(m2.level()) );
    Model m3(m3.geometry(), 3);
    CHECK( interval > m3.geometry().update_interval(m3.level()));
    interval = m3.geometry().update_interval(m3.level());
    m3.update();
    m3.update();
    m3.update();
    CHECK( interval == m3.geometry().update_interval(m3.level()));
}