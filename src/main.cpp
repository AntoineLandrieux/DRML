// DRML Snapshot 1.0
// Antoine Landrieux 2022

#include <iostream>
#include <fstream>
#include <console.hpp>
#include <errcode.hpp>
#define MAX_BUFFER 999

#pragma region VAR
bool console = false;
// INT
int BUFFER = 0;
int LINE_COUNT = 0;
// Function
void readFromFile(char fileName[]);
void Lexing();
#pragma endregion VAR

#include <execute.hpp>

int main(int argc, char *argv[])
{
    if (argv[1] == '\0')
    {
        console = true;
        consoleInit();
    }
    readFromFile(argv[1]);
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

void Lexing(std::string LINE)
{
    if (!console)
    {
        LINE_COUNT++;
    }
    bool CheckSpace = false;
    BUFFER = LINE.length()+1;
    if (BUFFER > MAX_BUFFER)
    {
        exit(EXIT_FAILURE);
    }
    char TOKENS_LINE[BUFFER];
    int a = 0;
    for (int i=0; i<LINE.length()+1; i++)
    {
        if (LINE[i]!=' ' && LINE[i]!='\t' && CheckSpace == false)
        {
            CheckSpace = true;
            TOKENS_LINE[a++] = LINE[i];
        }
        else if (CheckSpace == true)
        {
            TOKENS_LINE[a++] = LINE[i];
        }
    }
    Execute(TOKENS_LINE, BUFFER, LINE_COUNT, console);
}