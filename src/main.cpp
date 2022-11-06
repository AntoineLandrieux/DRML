// DRML Snapshot 1.0
// Antoine Landrieux 2022

#include <fstream>
#include <iostream>
#include <errcode.hpp>
#include <console.hpp>
#define MAX_BUFFER 999
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#pragma region VAR
// INT
int LINE_COUNT = 0;
// Function
int Lexing();
void readFromFile(char fileName[]);
#pragma endregion VAR

#include <execute.hpp>

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        consoleInit();
    }
    else
    {
        readFromFile(argv[1]);
        std::cout << "\nPress Enter for quit";
        getchar();
    }
    return EXIT_SUCCESS;
}

void readFromFile(char fileName[])
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
    else if (!getline(file, LINE))
    {
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
    if (Execute(TOKENS_LINE, BUFFER, LINE_COUNT, 0) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }
}
