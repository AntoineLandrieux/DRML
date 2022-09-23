#include <iostream>
#include <function.hpp>

void Lexing()
{
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
    LINE_COUNT++;
    Execute(TOKENS_LINE);
}
