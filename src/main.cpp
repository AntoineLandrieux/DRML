// DRML Snapshot 0.0.2
// Antoine Landrieux 2022

#include <iostream>
#include <fstream>
#define MAX_BUFFER 999

#pragma region VAR
// Strings
std::string LINE;
std::string VARIABLE_NAME_INT[MAX_BUFFER];
std::string VARIABLE_NAME_STRING[MAX_BUFFER];
std::string VARIABLE_VALUE_STRING[MAX_BUFFER];
// INT
int BUFFER = 0;
int LINE_COUNT = 0;
int VARIABLE_NUMBER_INT = 0;
int VARIABLE_NUMBER_STRING = 0;
int VARIABLE_VALUE_INT[MAX_BUFFER];
// Function
void readFromFile(char fileName[]);
void Lexing();
void Execute(char TOKENS_LINE[]);
#pragma endregion VAR

int main(int argc, char *argv[])
{
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

void Execute(char TOKENS_LINE[])
{
    bool str = false;
    bool VALIDATE = false;
    std::string IntTMP;
    std::string TMP[MAX_BUFFER];
    if (TOKENS_LINE[0] == '$')
    {
        for (int i = 1; i < BUFFER; i++)
        {
            if (TOKENS_LINE[i] != '=')
            {
                if ((TOKENS_LINE[i] == ' ') || (TOKENS_LINE[i] == '\t') || (TOKENS_LINE[i] == '\0'))
                {
                    exit(EXIT_FAILURE);
                }
                TMP[LINE_COUNT] += TOKENS_LINE[i];
            }
            else
            {
                for (int e = 0; e < VARIABLE_NUMBER_STRING; e++)
                {
                    if (TMP[LINE_COUNT] == VARIABLE_NAME_STRING[e])
                    {
                        exit(EXIT_FAILURE);
                    }
                }
                for (int e = 0; e < VARIABLE_NUMBER_INT; e++)
                {
                    if (TMP[LINE_COUNT] == VARIABLE_NAME_INT[e+1])
                    {
                        exit(EXIT_FAILURE);
                    }
                    if (TMP[LINE_COUNT] == VARIABLE_NAME_STRING[e+1])
                    {
                        exit(EXIT_FAILURE);
                    }
                }
                i++;
                if (TOKENS_LINE[i] == '\"')
                {
                    i++;
                    str = true;
                    VARIABLE_NUMBER_STRING++;
                    VARIABLE_NAME_STRING[VARIABLE_NUMBER_STRING] = TMP[LINE_COUNT];
                } else {
                    VARIABLE_NUMBER_INT++;
                    VARIABLE_NAME_INT[VARIABLE_NUMBER_INT] = TMP[LINE_COUNT];
                }
                for (i; i < BUFFER; i++)
                {
                    if ((TOKENS_LINE[i] != ';') || (str && TOKENS_LINE[i] != '\"' && TOKENS_LINE[i+1] != ';'))
                    {
                        if ((TOKENS_LINE[i] == '\0') || (TOKENS_LINE[i] == '~'))
                        {
                            exit(EXIT_FAILURE);
                        }
                        if (str && TOKENS_LINE[i]=='\"')
                        {
                            if (TOKENS_LINE[i+1]==';')
                            {
                                break;
                            } else {
                                exit(EXIT_FAILURE);
                            }
                        }
                        if (str)
                        {
                            VARIABLE_VALUE_STRING[VARIABLE_NUMBER_STRING] += TOKENS_LINE[i];
                        }
                        else
                        {
                            try
                            {
                                IntTMP += TOKENS_LINE[i];
                            }
                            catch (const std::exception& e)
                            {
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                    else
                    {
                        break;
                    }
                    try
                    {
                        if (!str)
                        {
                            int b = std::stoi(IntTMP);
                            VARIABLE_VALUE_INT[VARIABLE_NUMBER_INT] = b;
                        }
                    }
                    catch(const std::exception& e)
                    {
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            }
        }
    }
    else if (TOKENS_LINE[0] == '&')
    {
        int x = 1;
        std::string VAR[MAX_BUFFER];
        std::string VAR_CONTENT;
        VAR_CONTENT = "";
        for (x; x < BUFFER; x++)
        {
            if (TOKENS_LINE[x] != '=')
            {
                if ((TOKENS_LINE[x] == ' ') || (TOKENS_LINE[x] == '\t') || (TOKENS_LINE[x] == '\0'))
                {
                    exit(EXIT_FAILURE);
                }
                VAR[LINE_COUNT] += TOKENS_LINE[x];
            }
            else
            {
                break;
            }
        }
        x++;
        if (TOKENS_LINE[x]=='\"')
        {
            str = true;
            x++;
        }
        for (x; x < BUFFER; x++)
        {
            if (TOKENS_LINE[x] != ';')
            {
                if ((TOKENS_LINE[x] == '\0') || (TOKENS_LINE[x] == '~'))
                {
                    exit(EXIT_FAILURE);
                }
                if (str && TOKENS_LINE[x]=='\"')
                {
                    if (TOKENS_LINE[x+1]==';')
                    {
                        break;
                    } else {
                        exit(EXIT_FAILURE);
                    }
                }
                VAR_CONTENT += TOKENS_LINE[x];
            }
            else
            {
                break;
            }
        }
        for (int i = 0; i < MAX_BUFFER; i++)
        {
            if (VARIABLE_NAME_INT[i] == VAR[LINE_COUNT] || VARIABLE_NAME_STRING[i] == VAR[LINE_COUNT])
            {
                VALIDATE = true;
                if (str)
                {
                    VARIABLE_VALUE_STRING[i] = VAR_CONTENT;
                }
                else
                {
                    try
                    {
                        for (int e=0; i<VAR_CONTENT.length()+1; i++)
                        {
                            VARIABLE_VALUE_INT[i] = std::stoi(VAR_CONTENT);
                        }
                    }
                    catch(const std::exception& e)
                    {
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
        if (!VALIDATE)
        {
            exit(EXIT_FAILURE);
        }
    }
    else if (TOKENS_LINE[0] != '~')
    {
        if (TOKENS_LINE[0] != '\0')
        {
            exit(EXIT_FAILURE);
        }
    }
}