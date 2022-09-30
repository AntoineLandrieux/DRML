// DRML Snapshot 0.1.5
// Antoine Landrieux 2022

#include <iostream>
#include <fstream>
#define MAX_BUFFER 999

#pragma region VAR
// Strings
std::string LINE;
// INT
int PROCESS_ACTION[MAX_BUFFER];
int PROCESS_NUMBER = 0;
int BUFFER = 0;
int LINE_COUNT = 0;
// Function
void readFromFile(char fileName[]);
void Lexing();
#pragma endregion VAR

#include <execute.hpp>

int main(int argc, char *argv[])
{
    for (int i=0; i<MAX_BUFFER; i++)
    {
        PROCESS_ACTION[i] = 0;
    }
    readFromFile(argv[1]);
    return EXIT_SUCCESS;
}

void readFromFile(char fileName[])
{
    std::fstream file(fileName, std::ios::in);
    if (file.is_open())
    {
        while (getline(file, LINE))
        {
            Lexing();
        }
    }
    else if (!getline(file, LINE))
    {
        exit(EXIT_FAILURE);
    }
}

void Lexing()
{
    LINE_COUNT++;
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
    Execute(TOKENS_LINE, BUFFER, LINE_COUNT, PROCESS_ACTION, PROCESS_NUMBER);
}