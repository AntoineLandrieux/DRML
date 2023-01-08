// DRML Snapshot 22w2112a
// Antoine Landrieux 2022

#include <fstream>
#include <iostream>
#include <string>
#include <errcode.hpp>
#include <console.hpp>
#define MAX_BUFFER 999
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int LINE_COUNT = 0;
static void readFromFile(char fileName[]);

#include <execute.hpp>

int main(int argc, char **argv)
{
    if (argv[1] == NULL)
    {
        consoleInit();
    }
    else
    {
        for (int i=1; i<argc; i++)
        {
            readFromFile(argv[i]);
        }
        std::cout << "\nPress Enter for quit";
        getchar();
    }
    return EXIT_SUCCESS;
}

static void readFromFile(char fileName[])
{
    std::string LINE;
    std::fstream file(fileName, std::ios::in);
    if (file.is_open())
    {
        while (getline(file, LINE))
        {
            Lexing(LINE);
        }
    }
    else
    {
        ErrCode("FILE", "Can't open file", -1);
        exit(EXIT_FAILURE);
    }
}

int Lexing(std::string LINE)
{
    LINE_COUNT++;
    int CheckSpace = 0;
    int BUFFER = LINE.length()+1;
    if (BUFFER > MAX_BUFFER)
    {
        return EXIT_FAILURE;
    }
    char TOKENS_LINE[BUFFER];
    int a = 0;
    for (int i=0; i<LINE.length()+1; i++)
    {
        if (LINE[i]!=' ' && LINE[i]!='\t' && CheckSpace == 0)
        {
            CheckSpace = 1;
            TOKENS_LINE[a++] = LINE[i];
        }
        else if (CheckSpace == 1)
        {
            TOKENS_LINE[a++] = LINE[i];
        }
    }
    return Execute(TOKENS_LINE, BUFFER, LINE_COUNT, 0);
}
