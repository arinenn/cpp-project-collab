#include <iostream>
#include <cstdlib>

#include "src/my_add.hpp"

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Provide exactly 2 arguments." << std::endl;
        return 1;
    }

    int a = std::atoi(argv[1]);
    int b = std::atoi(argv[2]);

    std::cout << my_add(a, b) << std::endl;
    return 0;
}
