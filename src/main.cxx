#include "ui.hxx"
#include <set>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        UI game((Geometry()));
        game.run();
    } else if (argc == 2) {
        UI game(Geometry(), std::stoi(argv[1]));
        game.run();
    } else if (argc == 3) {
        UI game(Geometry(std::stoi(argv[1]), std::stoi(argv[2])));
        game.run();
    } else if (argc == 4) {
        UI game(Geometry(std::stoi(argv[1]), std::stoi(argv[2]))
        , std::stoi(argv[3]));
        game.run();
    }
 }
