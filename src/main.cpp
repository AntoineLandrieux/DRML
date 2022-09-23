// DRML Snapshot 0.1.5
// Antoine Landrieux 2022

#include <fstream>
#include <iostream>
#include <function.hpp>
#define MAX_BUFFER 999

#pragma region VARIABLE
// Strings
std::string LINE;
std::string VARIABLE_NAME_INT[MAX_BUFFER];
std::string VARIABLE_NAME_STRING[MAX_BUFFER];
std::string VARIABLE_VALUE_STRING[MAX_BUFFER];
// INT
int BUFFER = 0;
int LINE_COUNT = 0;
int PROCESS_NUMBER = 0;
int VARIABLE_NUMBER_INT = 0;
int VARIABLE_NUMBER_STRING = 0;
int PROCESS_ACTION[MAX_BUFFER];
int VARIABLE_VALUE_INT[MAX_BUFFER];
#pragma endregion VARIABLE

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

int main(int argc, char *argv[])
{
    for (int i=0; i<MAX_BUFFER; i++)
    {
        PROCESS_ACTION[i] = 0;
    }
    readFromFile(argv[1]);
    return EXIT_SUCCESS;
}
