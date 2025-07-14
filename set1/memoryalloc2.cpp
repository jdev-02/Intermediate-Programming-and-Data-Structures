#include <iostream>
#include <cstdlib>

int main (int argc, char *argv[])
{
    //p_int is a local variable that stores an addr
    int *p_int = new int(42);
    std::cout << p_int << std::endl;

    delete p_int;
    std::cout << p_int << std::endl;

    p_int = nullptr;
    std::cout << p_int << std::endl;

    return EXIT_SUCCESS;
}
