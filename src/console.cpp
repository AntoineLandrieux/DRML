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
    printf("DRML Snapshot 23w0501a 32Bits\nType \"exit;\" for quit\n");
    while (1)
    {
        printf("\n[%d] >>> ",Lexing(LINE));
        getline(std::cin, LINE);
    }
}