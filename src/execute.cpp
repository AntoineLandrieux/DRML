#include <iostream>
#include <string>
#include <errcode.hpp>
#include <execute.hpp>
#define MAX_BUFFER 999
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

std::string NAMESPACE = "\0";
std::string VARIABLE_NAME_INT[MAX_BUFFER];
std::string VARIABLE_NAME_STRING[MAX_BUFFER];
std::string VARIABLE_VALUE_STRING[MAX_BUFFER];
int PROCESS_ACTION[MAX_BUFFER];
int PROCESS_NUMBER = 0;
int VARIABLE_NUMBER_INT = 0;
int VARIABLE_NUMBER_STRING = 0;
int VARIABLE_VALUE_INT[MAX_BUFFER];

int Execute(char *TOKENS_LINE, int BUFFER, int LINE_COUNT, int LAST)
{
    int LAST_TOKEN = LAST;
    int str = 0;
    int result = 0;
    int VALIDATE = 0;
    char action = 'n';
    int final = 0;
    std::string VAR[MAX_BUFFER];
    std::string TMP[MAX_BUFFER];
    std::string VAR_CONTENT="";
    std::string IntTMP;
    VAR_CONTENT = "";
    if (TOKENS_LINE[LAST_TOKEN] == '$' && PROCESS_ACTION[PROCESS_NUMBER] != 1)
    {
        if (NAMESPACE != "\0")
        {
            TMP[LINE_COUNT] = NAMESPACE;
            TMP[LINE_COUNT] += ':';
            TMP[LINE_COUNT] += ':';
        }
        for (int i = 1; i < BUFFER; i++)
        {
            if (TOKENS_LINE[i] != '=')
            {
                if ((TOKENS_LINE[i] == ' ') || (TOKENS_LINE[i] == '\t') || (TOKENS_LINE[i] == '\0'))
                {
                    ErrCode("Incorrect Structure", "\'=\' missing", LINE_COUNT);
                    return EXIT_FAILURE;
                }
                TMP[LINE_COUNT] += TOKENS_LINE[i];
            }
            else
            {
                for (int e = 0; e < VARIABLE_NUMBER_STRING+1; e++)
                {
                    if (TMP[LINE_COUNT] == VARIABLE_NAME_STRING[e])
                    {
                        ErrCode("Incorrect argument", "Variable equ 1", LINE_COUNT);
                        return EXIT_FAILURE;
                    }
                }
                for (int e = 0; e < VARIABLE_NUMBER_INT+1; e++)
                {
                    if (TMP[LINE_COUNT] == VARIABLE_NAME_INT[e])
                    {
                        ErrCode("Incorrect argument", "Variable equ 1", LINE_COUNT);
                        return EXIT_FAILURE;
                    }
                }
                i++;
                if (TOKENS_LINE[i] == '\"')
                {
                    i++;
                    str = 1;
                    VARIABLE_NUMBER_STRING++;
                    VARIABLE_NAME_STRING[VARIABLE_NUMBER_STRING] = TMP[LINE_COUNT];
                }
                else
                {
                    VARIABLE_NUMBER_INT++;
                    VARIABLE_NAME_INT[VARIABLE_NUMBER_INT] = TMP[LINE_COUNT];
                }
                TMP[LINE_COUNT] = "";
                for (i; i < BUFFER; i++)
                {
                    if ((TOKENS_LINE[i] != ';') || (str && TOKENS_LINE[i] != '\"' && TOKENS_LINE[i+1] != ';'))
                    {
                        if ((TOKENS_LINE[i] == '\0') || (TOKENS_LINE[i] == '\r'))
                        {
                            ErrCode("Incorrect Structure", "\'\"\' missing", LINE_COUNT);
                            return EXIT_FAILURE;
                        }
                        if (str && TOKENS_LINE[i]=='\"')
                        {
                            if (TOKENS_LINE[i+1]==';')
                            {
                                LAST_TOKEN += i+1;
                                break;
                            }
                            else
                            {
                                ErrCode("Incorrect Structure", "\';\' missing", LINE_COUNT);
                                return EXIT_FAILURE;
                            }
                        }
                        if (str)
                        {
                            if (TOKENS_LINE[i] == '\\')
                            {
                                if (TOKENS_LINE[i+1] == 'n')
                                {
                                    VARIABLE_VALUE_STRING[VARIABLE_NUMBER_STRING] += '\n';
                                }
                                else if (TOKENS_LINE[i+1] == '\\')
                                {
                                    VARIABLE_VALUE_STRING[VARIABLE_NUMBER_STRING] += '\\';
                                }
                                else if (TOKENS_LINE[i+1] == '\"')
                                {
                                    VARIABLE_VALUE_STRING[VARIABLE_NUMBER_STRING] += '\"';
                                }
                                else if (TOKENS_LINE[i+1] == '\'')
                                {
                                    VARIABLE_VALUE_STRING[VARIABLE_NUMBER_STRING] += '\'';
                                }
                                else
                                {
                                    return EXIT_FAILURE;
                                    ErrCode("Incorrect Structure", "\'\\type\' incorrect value", LINE_COUNT);
                                }
                                i++;
                            }
                            else
                            {
                                VARIABLE_VALUE_STRING[VARIABLE_NUMBER_STRING] += TOKENS_LINE[i];
                            }
                        }
                        else
                        {
                            IntTMP += TOKENS_LINE[i];
                        }
                    }
                    else
                    {
                        LAST_TOKEN += i;
                        break;
                    }
                    if (!str)
                    {
                        int b = std::stoi(IntTMP);
                        VARIABLE_VALUE_INT[VARIABLE_NUMBER_INT] = b;
                    }
                }
                break;
            }
        }
    }
    else if (TOKENS_LINE[LAST_TOKEN] == '&' && PROCESS_ACTION[PROCESS_NUMBER] != 1)
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
                else if ((TOKENS_LINE[x] == '-'))
                {
                    action = '-';
                    break;
                }
                if ((TOKENS_LINE[x] == ' ') || (TOKENS_LINE[x] == '\t') || (TOKENS_LINE[x] == '\0'))
                {
                    ErrCode("Incorrect Structure", "\'=\' missing", LINE_COUNT);
                    return EXIT_FAILURE;
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
            str = 1;
            x++;
        }
        for (x; x < MAX_BUFFER; x++)
        {
            if (TOKENS_LINE[x] != ';')
            {
                if ((TOKENS_LINE[x] == '\0') || (TOKENS_LINE[x] == '\r'))
                {
                    ErrCode("Incorrect Structure", "\';\' missing", LINE_COUNT);
                    return EXIT_FAILURE;
                }
                if (str && TOKENS_LINE[x]=='\"')
                {
                    if (TOKENS_LINE[x+1]==';')
                    {
                        break;
                    }
                    else
                    {
                        ErrCode("Incorrect Structure", "\';\' missing", LINE_COUNT);
                        return EXIT_FAILURE;
                    }
                }
                if (str == 1 && TOKENS_LINE[x] == '\\')
                {
                    if (TOKENS_LINE[x+1] == 'n')
                    {
                        VAR_CONTENT += '\n';
                    }
                    else if (TOKENS_LINE[x+1] == '\\')
                    {
                        VAR_CONTENT += '\\';
                    }
                    else if (TOKENS_LINE[x+1] == '\"')
                    {
                        VAR_CONTENT += '\"';
                    }
                    else if (TOKENS_LINE[x+1] == '\'')
                    {
                        VAR_CONTENT += '\'';
                    }
                    else
                    {
                        return EXIT_FAILURE;
                        ErrCode("Incorrect Structure", "\'\\type\' incorrect value", LINE_COUNT);
                    }
                    x++;
                }
                else
                {
                    VAR_CONTENT += TOKENS_LINE[x];
                }
            }
            else
            {
                LAST_TOKEN += x;
                break;
            }
        }
        for (int i = 0; i < MAX_BUFFER; i++)
        {
            if (VARIABLE_NAME_INT[i] == VAR[LINE_COUNT] || VARIABLE_NAME_STRING[i] == VAR[LINE_COUNT])
            {
                VALIDATE = 1;
                if (str)
                {
                    if (action == '=')
                    {
                        VARIABLE_VALUE_STRING[i] = VAR_CONTENT;
                    }
                    else
                    {
                        ErrCode("Incorrect Structure", "Impossible action", LINE_COUNT);
                        return EXIT_FAILURE;
                    }
                }
                else
                {
                    if (action == '=')
                    {
                        VARIABLE_VALUE_INT[i] = std::stoi(VAR_CONTENT);
                    }
                    else if (action == '+')
                    {
                        VARIABLE_VALUE_INT[i] += std::stoi(VAR_CONTENT);
                    }
                    else if (action == '-')
                    {
                        VARIABLE_VALUE_INT[i] -= std::stoi(VAR_CONTENT);
                    }
                }
            }
        }
        if (!VALIDATE)
        {
            ErrCode("Incorrect Structure", " ", LINE_COUNT);
            return EXIT_FAILURE;
        }
    }
    else if (TOKENS_LINE[LAST_TOKEN] == 'i' && TOKENS_LINE[LAST_TOKEN+1] == 'f' && PROCESS_ACTION[PROCESS_NUMBER] != 1)
    {
        int i=LAST_TOKEN+4;
        for (i; i<BUFFER; i++)
        {
            if (TOKENS_LINE[LAST_TOKEN+3] == '$')
            {
                if ((TOKENS_LINE[i] == '\t') || (TOKENS_LINE[i] == '\0') || (TOKENS_LINE[i] == ';'))
                {
                    ErrCode("Incorrect Structure", "value missing", LINE_COUNT);
                    return EXIT_FAILURE;
                }
                if (TOKENS_LINE[i] == ' ')
                {
                    break;
                }
                VAR[LINE_COUNT] += TOKENS_LINE[i];
            }
            else
            {
                ErrCode("Incorrect Structure", "Variable value missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
        int v=0;
        for (v; v<MAX_BUFFER; v++)
        {
            if (VARIABLE_NAME_INT[v] == VAR[LINE_COUNT])
            {
                str = 0;
                VALIDATE = 1;
                break;
            }
            else if (VARIABLE_NAME_STRING[v] == VAR[LINE_COUNT])
            {
                str = 1;
                VALIDATE = 1;
                break;
            }
        }
        if (!VALIDATE)
        {
            ErrCode("Incorrect Structure", "Variable missing", LINE_COUNT);
            return EXIT_FAILURE;
        }
        VALIDATE = 0;
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
                ErrCode("Incorrect Structure", "\';\' missing", LINE_COUNT);
                return EXIT_FAILURE;
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
            ErrCode("Incorrect Structure", "Enter an valid action", LINE_COUNT);
            return EXIT_FAILURE;
        }
        i++;
        if (TOKENS_LINE[i] != '$')
        {
            ErrCode("Incorrect Structure", "Variable value missing", LINE_COUNT);
            return EXIT_FAILURE;
        }
        LINE_COUNT++;
        i+=1;
        for (i; i<BUFFER; i++)
        {
            if (TOKENS_LINE[i] != ' ')
            {
                if ((TOKENS_LINE[i] == '\t') || (TOKENS_LINE[i] == '\0'))
                {
                    ErrCode("Incorrect Structure", "Value missing", LINE_COUNT-1);
                    return EXIT_FAILURE;
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
            if (TMP[LINE_COUNT] == VARIABLE_NAME_STRING[bnb])
            {
                VALIDATE = 1;
                break;
            }
            if (TMP[LINE_COUNT] == VARIABLE_NAME_INT[bnb])
            {
                VALIDATE = 1;
                break;
            }
        }
        if (VALIDATE == 0)
        {
            ErrCode("Incorrect Structure", "Variable missing", LINE_COUNT-1);
            return EXIT_FAILURE;
        }
        VALIDATE = 0;
        if (str)
        {
            TMP[LINE_COUNT] = VARIABLE_VALUE_STRING[i];
            VALIDATE = 1;
        }
        else
        {
            TMP[LINE_COUNT] = VARIABLE_VALUE_INT[i];
            VALIDATE = 1;
        }
        if (!VALIDATE)
        {
            ErrCode("Incorrect Structure", " ", LINE_COUNT);
            return EXIT_FAILURE;
        }
        VALIDATE = 0;
        if (action == '=')
        {
            if ((str == 0) && (VARIABLE_VALUE_INT[v] == VARIABLE_VALUE_INT[bnb]))
            {
                result = 1;
            }
            else if ((str == 0) && (VARIABLE_VALUE_INT[v] != VARIABLE_VALUE_INT[bnb]))
            {
                result = 0;
            }
            if ((str == 1) && (VARIABLE_VALUE_STRING[v] == VARIABLE_VALUE_STRING[bnb]))
            {
                result = 1;
            }
            else if ((str == 1) && (VARIABLE_VALUE_STRING[v] != VARIABLE_VALUE_STRING[bnb]))
            {
                result = 0;
            }
        }
        if (action == '!')
        {
            if (str == 0 && VARIABLE_VALUE_INT[v] != VARIABLE_VALUE_INT[bnb])
            {
                result = 1;
            }
            else if (str == 0 && VARIABLE_VALUE_INT[v] == VARIABLE_VALUE_INT[bnb])
            {
                result = 0;
            }
            if (str == 1 && VARIABLE_VALUE_STRING[v] != VARIABLE_VALUE_STRING[bnb])
            {
                result = 1;
            }
            else if (str == 1 && VARIABLE_VALUE_STRING[v] == VARIABLE_VALUE_STRING[bnb])
            {
                result = 0;
            }
        }
        if (action == '<')
        {
            if (!str && VARIABLE_VALUE_INT[v] <= VARIABLE_VALUE_INT[bnb])
            {
                result = 1;
            }
            else if (!str && VARIABLE_VALUE_INT[v] <= VARIABLE_VALUE_INT[bnb])
            {
                result = 0;
            }
            if (str)
            {
                ErrCode("Incorrect Structure", "Can't compare str with \'<\'", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
        if (action == '>')
        {
            if (!str && VARIABLE_VALUE_INT[v] >= VARIABLE_VALUE_INT[bnb])
            {
                result = 1;
            }
            else if (!str && VARIABLE_VALUE_INT[v] >= VARIABLE_VALUE_INT[bnb])
            {
                result = 0;
            }
            if (str)
            {
                ErrCode("Incorrect Structure", "Can't compare str with \'>\'", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
        i--;
        LINE_COUNT--;
        TMP[LINE_COUNT] = "";
        if (TOKENS_LINE[i] == 'e' && TOKENS_LINE[i+1] == 'x' && TOKENS_LINE[i+2] == 'e' && TOKENS_LINE[i+3] == 'c')
        {
            i+=4;
            PROCESS_NUMBER++;
            if (result != 1)
            {
                PROCESS_ACTION[PROCESS_NUMBER] = 1;
            }
            for (i; i<BUFFER; i++)
            {
                if (TOKENS_LINE[i]=='\t' || TOKENS_LINE[i]==' ')
                {
                    continue;
                }
                else if (TOKENS_LINE[i]==':' && final==0)
                {
                    final=1;
                    LAST_TOKEN += i;
                    break;
                }
                else
                {
                    ErrCode("Incorrect Structure", "\':\' missing", LINE_COUNT);
                    return EXIT_FAILURE;
                }
            }
        }
        else
        {
            ErrCode("Incorrect Structure", "\'exec\' missing", LINE_COUNT);
            return EXIT_FAILURE;
        }
    }
    else if ((TOKENS_LINE[LAST_TOKEN] == 'e') && (TOKENS_LINE[LAST_TOKEN+1] == 'n') && (TOKENS_LINE[LAST_TOKEN+2] == 'd'))
    {
        int i = LAST_TOKEN+3;
        for (i; i<BUFFER; i++)
        {
            if (TOKENS_LINE[i]=='\t' || TOKENS_LINE[i]==' ')
            {
                continue;
            }
            else if (TOKENS_LINE[i] == ';' && final==0)
            {
                final=1;
                LAST_TOKEN += i;
                if (PROCESS_NUMBER == 0)
                {
                    ErrCode("PROCESS", "Process equ 0", LINE_COUNT);
                    return EXIT_FAILURE;
                }
                if (PROCESS_ACTION[PROCESS_NUMBER] == 2)
                {
                    NAMESPACE = "\0";
                }
                PROCESS_ACTION[PROCESS_NUMBER] = 0;
                PROCESS_NUMBER--;
                break;
            }
            else
            {
                ErrCode("Incorrect Structure", "\';\' missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
    }
    else if ((TOKENS_LINE[LAST_TOKEN] == 'e') && (TOKENS_LINE[LAST_TOKEN+1] == 'l') && (TOKENS_LINE[LAST_TOKEN+2] == 's') && (TOKENS_LINE[LAST_TOKEN+3] == 'e'))
    {
        for (int i=LAST_TOKEN+4; i< BUFFER; i++)
        {
            if (TOKENS_LINE[i]==' ' || TOKENS_LINE[i]=='\t')
            {
                continue;
            }
            else if (TOKENS_LINE[i]==':')
            {
                LAST_TOKEN += i;
                if (PROCESS_NUMBER <= 0 || PROCESS_ACTION[PROCESS_NUMBER] == 2)
                {
                    ErrCode("Incorrect Structure", "\'if\' missing", LINE_COUNT);
                    return EXIT_FAILURE;
                }
                if (PROCESS_ACTION[PROCESS_NUMBER] == 0)
                {
                    PROCESS_ACTION[PROCESS_NUMBER] = 1;
                }
                else if (PROCESS_ACTION[PROCESS_NUMBER] == 1)
                {
                    PROCESS_ACTION[PROCESS_NUMBER] = 0;
                }
                else
                {
                    ErrCode("Incorrect Structure", "\':\' missing", LINE_COUNT);
                    return EXIT_FAILURE;
                }
                break;
            }
            else
            {
                ErrCode("Incorrect Structure", "\':\' missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
    }
    else if ((TOKENS_LINE[LAST_TOKEN] == 'o') && (TOKENS_LINE[LAST_TOKEN+1] == 'u') && (TOKENS_LINE[LAST_TOKEN+2] == 't') && (PROCESS_ACTION[PROCESS_NUMBER] != 1))
    {
        int isVar = 0;
        int i = LAST_TOKEN+4;
        for (i; i < BUFFER; i++)
        {
            if (TOKENS_LINE[i]==' ' | TOKENS_LINE[i]=='\t')
            {
                continue;
            }
            else if (TOKENS_LINE[i]=='\"')
            {
                break;
            }
            else if (TOKENS_LINE[i]=='$')
            {
                isVar = 1;
                break;
            }
            else
            {
                ErrCode("Incorrect Structure", "\'\"\' or variable missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
        i++;
        for (i; i< BUFFER; i++)
        {
            if (TOKENS_LINE[i] == '\0' || TOKENS_LINE[i] == '\r')
            {
                ErrCode("Incorrect Structure", "\'\"\' missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
            if (TOKENS_LINE[i] == '\"' && isVar == 0)
            {
                i++;
                break;
            }
            if (TOKENS_LINE[i] == ' ' && isVar == 1)
            {
                i++;
                break;
            }
            if (TOKENS_LINE[i] == ';' && isVar == 1)
            {
                break;
            }
            if (isVar == 0 && TOKENS_LINE[i] == '\\')
            {
                if (TOKENS_LINE[i+1] == 'n')
                {
                    TMP[LINE_COUNT] += '\n';
                }
                else if (TOKENS_LINE[i+1] == '\\')
                {
                    TMP[LINE_COUNT] += '\\';
                }
                else if (TOKENS_LINE[i+1] == '\"')
                {
                    TMP[LINE_COUNT] += '\"';
                }
                else if (TOKENS_LINE[i+1] == '\'')
                {
                    TMP[LINE_COUNT] += '\'';
                }
                else
                {
                    return EXIT_FAILURE;
                    ErrCode("Incorrect Structure", "\'\\type\' incorrect value", LINE_COUNT);
                }
                i++;
            }
            else
            {
                TMP[LINE_COUNT] += TOKENS_LINE[i];
            }
        }
        for (i; i < BUFFER; i++)
        {
            if (TOKENS_LINE[i]==' ' || TOKENS_LINE[i]=='\t')
            {
                continue;
            }
            else if (TOKENS_LINE[i]==';')
            {
                LAST_TOKEN = i;
                VALIDATE = 1;
                break;
            }
            else
            {
                ErrCode("Incorrect Structure", "\';\' missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
        if (VALIDATE == 1)
        {
            if (isVar == 1)
            {
                str = 0;
                VALIDATE = 0;
                int e = 0;
                for (e; e < MAX_BUFFER; e++)
                {
                    if (TMP[LINE_COUNT] == VARIABLE_NAME_STRING[e])
                    {
                        str = 1;
                        VALIDATE = 1;
                        break;
                    }
                }
                if (VALIDATE != 1)
                {
                    e = 0;
                    for (e; e < MAX_BUFFER; e++)
                    {
                        if (TMP[LINE_COUNT] == VARIABLE_NAME_INT[e])
                        {
                            VALIDATE = 1;
                            break;
                        }
                    }
                }
                if (VALIDATE == 0) {
                    ErrCode("Incorrect Structure", "Variable missing", LINE_COUNT);
                    return EXIT_FAILURE;
                }
                if (str == 1)
                {
                    std::cout << VARIABLE_VALUE_STRING[e];
                }
                else
                {
                    std::cout << VARIABLE_VALUE_INT[e];
                }
            }
            else
            {
                std::cout << TMP[LINE_COUNT];
            }
        }
    }
    else if ((TOKENS_LINE[LAST_TOKEN] == 'i') && (TOKENS_LINE[LAST_TOKEN+1] == 'n') && (PROCESS_ACTION[PROCESS_NUMBER] != 1))
    {
        int i = LAST_TOKEN+3;
        for (i; i < BUFFER; i++)
        {
            if (TOKENS_LINE[i]==' ' | TOKENS_LINE[i]=='\t')
            {
                continue;
            }
            else if (TOKENS_LINE[i]=='$')
            {
                break;
            }
            else
            {
                ErrCode("Incorrect Structure", "variable missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
        i++;
        for (i; i< BUFFER; i++)
        {
            if (TOKENS_LINE[i] == '\0' || TOKENS_LINE[i] == '\r')
            {
                ErrCode("Incorrect Structure", "; missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
            else if (TOKENS_LINE[i] == ';' || TOKENS_LINE[i] == ' ')
            {
                break;
            }
            else
            {
                TMP[LINE_COUNT] += TOKENS_LINE[i];
            }
        }
        for (i; i < BUFFER; i++)
        {
            if (TOKENS_LINE[i]==' ' || TOKENS_LINE[i]=='\t')
            {
                continue;
            }
            else if (TOKENS_LINE[i]==';')
            {
                LAST_TOKEN = i;
                VALIDATE = 1;
                break;
            }
            else
            {
                ErrCode("Incorrect Structure", "\';\' missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
        if (VALIDATE == 1)
        {
            str = 0;
            VALIDATE = 0;
            int e = 0;
            for (e; e < MAX_BUFFER; e++)
            {
                if (TMP[LINE_COUNT] == VARIABLE_NAME_STRING[e])
                {
                    str = 1;
                    VALIDATE = 1;
                    break;
                }
            }
            if (VALIDATE != 1)
            {
                e = 0;
                for (e; e < MAX_BUFFER; e++)
                {
                    if (TMP[LINE_COUNT] == VARIABLE_NAME_INT[e])
                    {
                        VALIDATE = 1;
                        break;
                    }
                }
            }
            if (VALIDATE == 0) {
                ErrCode("Incorrect Structure", "Variable missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
            if (str == 1)
            {
                getline(std::cin, VARIABLE_VALUE_STRING[e]);
            }
            else
            {
                ErrCode("Incorrect Structure", "Can\'t convert <int> to <string>", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
    }
    else if ((TOKENS_LINE[LAST_TOKEN] == 'n') && (TOKENS_LINE[LAST_TOKEN+1] == 'a') && (TOKENS_LINE[LAST_TOKEN+2] == 'm') && (TOKENS_LINE[LAST_TOKEN+3] == 'e') && (TOKENS_LINE[LAST_TOKEN+4] == 's') && (TOKENS_LINE[LAST_TOKEN+5] == 'p') && (TOKENS_LINE[LAST_TOKEN+6] == 'a') && (TOKENS_LINE[LAST_TOKEN+7] == 'c') && (TOKENS_LINE[LAST_TOKEN+8] == 'e') && (PROCESS_ACTION[PROCESS_NUMBER] != 1))
    {
        VALIDATE = 0;
        if (NAMESPACE != "\0")
        {
            ErrCode("Incorrect Structure", "Can\'t place tow namespace", LINE_COUNT);
            return EXIT_FAILURE;
        }
        int i = LAST_TOKEN+9;
        for (i; i<BUFFER; i++)
        {
            if ((TOKENS_LINE[i]==' ' || TOKENS_LINE[i]=='\t') && (VALIDATE == 0))
            {
                continue;
            }
            else if (TOKENS_LINE[i]==' ' && VALIDATE == 1)
            {
                i++;
                break;
            }
            else if (TOKENS_LINE[i]==':' && VALIDATE == 1)
            {
                break;
            }
            else if (TOKENS_LINE[i]=='~' || TOKENS_LINE[i]=='\0' || TOKENS_LINE[i]=='\r')
            {
                ErrCode("Incorrect Structure", "\':\' missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
            else
            {
                VALIDATE = 1;
                TMP[LINE_COUNT] += TOKENS_LINE[i];
            }
        }
        VALIDATE = 0;
        for (i; i < BUFFER; i++)
        {
            if ((TOKENS_LINE[i]==' ' || TOKENS_LINE[i]=='\t'))
            {
                continue;
            }
            else if (TOKENS_LINE[i]==':')
            {
                break;
            }
            else
            {
                ErrCode("Incorrect Structure", "\':\' missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
        PROCESS_NUMBER++;
        PROCESS_ACTION[PROCESS_NUMBER] = 2;
        NAMESPACE = TMP[LINE_COUNT];
    }
    else if ((TOKENS_LINE[LAST_TOKEN] == 'e') && (TOKENS_LINE[LAST_TOKEN+1] == 'x') && (TOKENS_LINE[LAST_TOKEN+2] == 'i') && (TOKENS_LINE[LAST_TOKEN+3] == 't') && (PROCESS_ACTION[PROCESS_NUMBER] != 1))
    {
        for (int i=LAST_TOKEN+4; i< BUFFER; i++)
        {
            if (TOKENS_LINE[i]==' ' || TOKENS_LINE[i]=='\t')
            {
                continue;
            }
            else if (TOKENS_LINE[i]==';')
            {
                exit(EXIT_SUCCESS);
            }
            else
            {
                ErrCode("Incorrect Structure", "\';\' missing", LINE_COUNT);
                return EXIT_FAILURE;
            }
        }
    }
    else if ((TOKENS_LINE[LAST_TOKEN] == 'e') && (TOKENS_LINE[LAST_TOKEN+1] == 'x') && (TOKENS_LINE[2] == 'i') && (TOKENS_LINE[LAST_TOKEN+3] == 't') && (PROCESS_ACTION[PROCESS_NUMBER] == 1));
    else if ((TOKENS_LINE[LAST_TOKEN] == 'o') && (TOKENS_LINE[LAST_TOKEN+1] == 'u') && (TOKENS_LINE[2] == 't') && (PROCESS_ACTION[PROCESS_NUMBER] == 1));
    else if ((TOKENS_LINE[LAST_TOKEN] == '$' && PROCESS_ACTION[PROCESS_NUMBER] == 1) || (TOKENS_LINE[0] == '&' && PROCESS_ACTION[PROCESS_NUMBER] == 1));
    else if (TOKENS_LINE[LAST_TOKEN] == ' ' || TOKENS_LINE[LAST_TOKEN] == '\t');
    else if (TOKENS_LINE[LAST_TOKEN] != '~')
    {
        if (TOKENS_LINE[LAST_TOKEN] != '\0')
        {
            return EXIT_FAILURE;
        } else {
            LAST_TOKEN = 0;
            return EXIT_SUCCESS;
        }
    }
    else
    {
        LAST_TOKEN = 0;
        return EXIT_SUCCESS;
    }
    Execute(TOKENS_LINE, BUFFER, LINE_COUNT, LAST_TOKEN+1);
    return EXIT_SUCCESS;
}
