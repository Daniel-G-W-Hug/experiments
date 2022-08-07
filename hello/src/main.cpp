#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Hello World!\n";

    do
    {
        std::cout << '\n'
                  << "Press ENTER to continue...";
    } while (std::cin.get() != '\n');

    return 0;
}