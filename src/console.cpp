#include <iostream>
#include <console.hpp>
#include <errcode.hpp>

void consoleInit()
{
    std::string LINE;
    std::cout << "DRML Snapshot 1.0 on win32\nType \"exit;\" for quit\n" << std::endl;
    while (1)
    {
        std::cout << ">>> ";
        getline(std::cin, LINE);
        Lexing(LINE);
    }
}