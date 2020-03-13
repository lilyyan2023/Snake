#include "ui.hxx"
#include <set>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        UI(Geometry()).run();
    } else if (argc == 2) {
        UI(Geometry(), std::stoi(argv[1])).run();
    } else if (argc == 3) {
        UI(Geometry(std::stoi(argv[1]), std::stoi(argv[2]))).run();
    } else if (argc == 4) {
        UI(Geometry(std::stoi(argv[1]), std::stoi(argv[2]))
        , std::stoi(argv[3])).run();
    }
 }
