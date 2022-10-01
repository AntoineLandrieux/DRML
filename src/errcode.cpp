#include <iostream>
#include <errcode.hpp>

void ErrCode(std::string type, std::string message, int LINE_COUNT, bool console)
{
    std::cerr << type << " : " << message << "\nA la ligne : " << LINE_COUNT << std::endl;
    if (!console)
    {
        exit(EXIT_FAILURE);
    }
}