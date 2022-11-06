#include <stdio.h>
#include <iostream>
#include <errcode.hpp>
#include <console.hpp>
#define MAX_BUFFER 999
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void consoleInit()
{
    std::string LINE;
    printf("DRML Snapshot 1.0 on win32\nType \"exit;\" for quit\n\n");
    while (1)
    {
        printf(">>> ");
        getline(std::cin, LINE);
        Lexing(LINE);
    }
}