#include <iostream>
#include <cstdlib>

int main (int argc, char *argv[])
{
    //p_int is a local variable that stores an addr
    int *p_int;
    p_int = new int(42);

    //int *p_int = new int(42);
    //int *p_int{new int(42)};

    std::cout << p_int << std::endl;
    return EXIT_SUCCESS;
}
