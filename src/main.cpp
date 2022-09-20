// DRML Snapshot 0.1.5
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
int PROCESS_NUMBER = 0;
int VARIABLE_NUMBER_INT = 0;
int VARIABLE_NUMBER_STRING = 0;
int PROCESS_ACTION[MAX_BUFFER];
int VARIABLE_VALUE_INT[MAX_BUFFER];
// Function
void readFromFile(char fileName[]);
void Lexing();
void Execute(char TOKENS_LINE[]);
#pragma endregion VAR

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
    bool result = false;
    bool VALIDATE = false;
    char action = 'n';
    std::string VAR[MAX_BUFFER];
    std::string TMP[MAX_BUFFER];
    std::string VAR_CONTENT="";
    std::string IntTMP;
    VAR_CONTENT = "";
    if (TOKENS_LINE[0] == '$' && PROCESS_ACTION[PROCESS_NUMBER] != 1)
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
    else if (TOKENS_LINE[0] == '&' && PROCESS_ACTION[PROCESS_NUMBER] != 1)
    {
        int x = 1;
        for (x; x < BUFFER; x++)
        {
            if (TOKENS_LINE[x] != '=')
            {
                if ((TOKENS_LINE[x] == '+'))
                {
                    action = '+';
                    break;
                }
                if ((TOKENS_LINE[x] == ' ') || (TOKENS_LINE[x] == '\t') || (TOKENS_LINE[x] == '\0'))
                {
                    exit(EXIT_FAILURE);
                }
                VAR[LINE_COUNT] += TOKENS_LINE[x];
            }
            else
            {
                action = '=';
                break;
            }
        }
        x++;
        if (TOKENS_LINE[x]=='\"')
        {
            str = true;
            x++;
        }
        for (x; x < MAX_BUFFER; x++)
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
                    if (action == '=')
                    {
                        VARIABLE_VALUE_STRING[i] = VAR_CONTENT;
                    }
                    else
                    {
                        exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    try
                    {
                        if (action == '=')
                        {
                            VARIABLE_VALUE_INT[i] = std::stoi(VAR_CONTENT);
                        }
                        else if (action == '+')
                        {
                            VARIABLE_VALUE_INT[i] += std::stoi(VAR_CONTENT);
                        }
                        else
                        {
                            VARIABLE_VALUE_INT[i] -= std::stoi(VAR_CONTENT);
                        }
                    }
                    catch(const std::exception& f)
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
    else if (TOKENS_LINE[0] == 'i' && TOKENS_LINE[1] == 'f' && PROCESS_ACTION[PROCESS_NUMBER] != 1)
    {
        int i=4;
        for (i; i<BUFFER; i++)
        {
            if (TOKENS_LINE[3] == '$')
            {
                if ((TOKENS_LINE[i] == '\t') || (TOKENS_LINE[i] == '\0') || (TOKENS_LINE[i] == ';'))
                {
                    exit(EXIT_FAILURE);
                }
                if (TOKENS_LINE[i] == ' ')
                {
                    break;
                }
                VAR[LINE_COUNT] += TOKENS_LINE[i];
            } else {
                exit(EXIT_FAILURE);
            }
        }
        int v=0;
        for (v; v<MAX_BUFFER; v++)
        {
            if (VARIABLE_NAME_INT[v] == VAR[LINE_COUNT])
            {
                str = false;
                VALIDATE = true;
                break;
            }
            else if (VARIABLE_NAME_STRING[v] == VAR[LINE_COUNT])
            {
                str = true;
                VALIDATE = true;
                break;
            }
        }
        if (!VALIDATE)
        {
            exit(EXIT_FAILURE);
        }
        VALIDATE = false;
        if (str)
        {
            TMP[LINE_COUNT] = VARIABLE_VALUE_STRING[v];
        }
        else
        {
            TMP[LINE_COUNT] = VARIABLE_VALUE_INT[v];
        }
        i++;
        for (i; i< BUFFER; i++)
        {
            if ((TOKENS_LINE[i] == '\t') || (TOKENS_LINE[i] == '\0') || (TOKENS_LINE[i] == ';'))    
            {
                exit(EXIT_FAILURE);
            }
            if (TOKENS_LINE[i] == ' ')
            {
                break;
            }
            if ((TOKENS_LINE[i] == '<' && TOKENS_LINE[i+1] == '=') || (TOKENS_LINE[i] == '=' && TOKENS_LINE[i+1] == '<'))
            {
                action = '<';
            }
            if ((TOKENS_LINE[i] == '>' && TOKENS_LINE[i+1] == '=') || (TOKENS_LINE[i] == '=' && TOKENS_LINE[i+1] == '>'))
            {
                action = '>';
            }
            if ((TOKENS_LINE[i] == '!' && TOKENS_LINE[i+1] == '=') || (TOKENS_LINE[i] == '=' && TOKENS_LINE[i+1] == '!'))
            {
                action = '!';
            }
            if (TOKENS_LINE[i] == '=' && TOKENS_LINE[i+1] == '=')
            {
                action = '=';
            }
        }
        if (action == 'n')
        {
            exit(EXIT_FAILURE);
        }
        i++;
        if (TOKENS_LINE[i] != '$')
        {
            exit(EXIT_FAILURE);
        }
        LINE_COUNT++;
        i+=1;
        for (i; i<BUFFER; i++)
        {
            if (TOKENS_LINE[i] != ' ')
            {
                if ((TOKENS_LINE[i] == '\t') || (TOKENS_LINE[i] == '\0'))
                {
                    exit(EXIT_FAILURE);
                }
                TMP[LINE_COUNT] += TOKENS_LINE[i];
            } else {
                break;
            }
        }
        i+=2;
        int bnb=0;
        for (bnb; bnb < MAX_BUFFER; bnb++)
        {
            if (std::string(TMP[LINE_COUNT]) == std::string(VARIABLE_NAME_STRING[bnb]))
            {
                VALIDATE = true;
                break;
            }
            if (std::string(TMP[LINE_COUNT]) == std::string(VARIABLE_NAME_INT[bnb]))
            {
                VALIDATE = true;
                break;
            }
        }
        if (VALIDATE == false)
        {
            exit(EXIT_FAILURE);
        }
        if (str)
        {
            TMP[LINE_COUNT] = VARIABLE_VALUE_STRING[i];
            VALIDATE = true;
        }
        else
        {
            TMP[LINE_COUNT] = VARIABLE_VALUE_INT[i];
            VALIDATE = true;
        }
        if (!VALIDATE)
        {
            exit(EXIT_FAILURE);
        }
        VALIDATE = false;
        if (action == '=')
        {
            if ((str == false) && (VARIABLE_VALUE_INT[v] == VARIABLE_VALUE_INT[bnb]))
            {
                result = true;
            }
            else if ((str == false) && (VARIABLE_VALUE_INT[v] != VARIABLE_VALUE_INT[bnb]))
            {
                result = false;
            }
            if ((str == true) && (VARIABLE_VALUE_STRING[v] == VARIABLE_VALUE_STRING[bnb]))
            {
                result = true;
            }
            else if ((str == true) && (VARIABLE_VALUE_STRING[v] != VARIABLE_VALUE_STRING[bnb]))
            {
                result = false;
            }
        }
        if (action == '!')
        {
            if (str == false && VARIABLE_VALUE_INT[v] != VARIABLE_VALUE_INT[bnb])
            {
                result = true;
            }
            else if (str == false && VARIABLE_VALUE_INT[v] == VARIABLE_VALUE_INT[bnb])
            {
                result = false;
            }
            if (str == true && VARIABLE_VALUE_STRING[v] != VARIABLE_VALUE_STRING[bnb])
            {
                result = true;
            }
            else if (str == true && VARIABLE_VALUE_STRING[v] == VARIABLE_VALUE_STRING[bnb])
            {
                result = false;
            }
        }
        if (action == '<')
        {
            if (!str && VARIABLE_VALUE_INT[v] <= VARIABLE_VALUE_INT[bnb])
            {
                result = true;
            }
            else if (!str && VARIABLE_VALUE_INT[v] <= VARIABLE_VALUE_INT[bnb])
            {
                result = false;
            }
            if (str)
            {
                exit(EXIT_FAILURE);
            }
        }
        if (action == '>')
        {
            if (!str && VARIABLE_VALUE_INT[v] >= VARIABLE_VALUE_INT[bnb])
            {
                result = true;
            }
            else if (!str && VARIABLE_VALUE_INT[v] >= VARIABLE_VALUE_INT[bnb])
            {
                result = false;
            }
            if (str)
            {
                exit(EXIT_FAILURE);
            }
        }
        i--;
        LINE_COUNT--;
        TMP[LINE_COUNT] = "";
        if (TOKENS_LINE[i] == 'e' && TOKENS_LINE[i+1] == 'x' && TOKENS_LINE[i+2] == 'e' && TOKENS_LINE[i+3] == 'c')
        {
            if (result != true)
            {
                PROCESS_NUMBER++;
                PROCESS_ACTION[PROCESS_NUMBER] = 1;
            }
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    else if ((TOKENS_LINE[0] == 'e') && (TOKENS_LINE[1] == 'n') && (TOKENS_LINE[2] == 'd'))
    {
        if (TOKENS_LINE[3] == ';')
        {
            PROCESS_ACTION[PROCESS_NUMBER] = 0;   
            PROCESS_NUMBER--;
        } else {
            exit(EXIT_FAILURE);
        }
    }
    else if ((TOKENS_LINE[0] == 'o') && (TOKENS_LINE[1] == 'u') && (TOKENS_LINE[2] == 't') && (PROCESS_ACTION[PROCESS_NUMBER] != 1))
    {
        int i = 4;
        if (TOKENS_LINE[i] != '\"')
        {
            exit(EXIT_FAILURE);
        }
        i++;
        for (i; i< BUFFER; i++)
        {
            if (TOKENS_LINE[i] == '\0' || TOKENS_LINE[i] == ';')
            {
                exit(EXIT_FAILURE);
            }
            if (TOKENS_LINE[i] == '\"')
            {
                if (TOKENS_LINE[i+1] == ';')
                {
                    break;
                }
                else
                {
                    exit(EXIT_FAILURE);
                }
            }
            TMP[LINE_COUNT] += TOKENS_LINE[i];
        }
        std::cout << TMP[LINE_COUNT] << std::endl;
    }
    else if ((TOKENS_LINE[0] == 'e') && (TOKENS_LINE[1] == 'x') && (TOKENS_LINE[2] == 'i') && (TOKENS_LINE[3] == 't') && (PROCESS_ACTION[PROCESS_NUMBER] != 1))
    {
        if (TOKENS_LINE[4] == ';')
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    else if ((TOKENS_LINE[0] == 'e') && (TOKENS_LINE[1] == 'x') && (TOKENS_LINE[2] == 'i') && (TOKENS_LINE[3] == 't') && (PROCESS_ACTION[PROCESS_NUMBER] == 1));
    else if ((TOKENS_LINE[0] == 'o') && (TOKENS_LINE[1] == 'u') && (TOKENS_LINE[2] == 't') && (PROCESS_ACTION[PROCESS_NUMBER] == 1));
    else if ((TOKENS_LINE[0] == '$' && PROCESS_ACTION[PROCESS_NUMBER] == 1) || (TOKENS_LINE[0] == '&' && PROCESS_ACTION[PROCESS_NUMBER] == 1));
    else if (TOKENS_LINE[0] != '~')
    {
        if (TOKENS_LINE[0] != '\0')
        {
            exit(EXIT_FAILURE);
        }
    }
}