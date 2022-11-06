#include <stdio.h>
#include <iostream>
#include <errcode.hpp>

void ErrCode(std::string type, std::string message, int LINE_COUNT)
{
    std::cout << type << " : " << message << "\nA la ligne : " << LINE_COUNT << std::endl;
}