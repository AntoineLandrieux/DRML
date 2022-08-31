// DRML Snapshot 0.0.111
// Antoine Landrieux 2022

#include <iostream>
#include <fstream>
#define MAX_BUFFER 999

#pragma region VAR
// Strings
std::string LINE;
std::string VARIABLE_NAME[MAX_BUFFER];
std::string VARIABLE_VALUE[MAX_BUFFER];
// INT
int LINE_COUNT = 0;
int BUFFER = 0;
int VARIABLE_NUMBER = 0;
int BREAK_POINT = 0;
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
  BUFFER = LINE.length()+1;
  if (BUFFER > MAX_BUFFER)
  {
    exit(EXIT_FAILURE);
  }
  char TOKENS_LINE[BUFFER];
  for (int i=0; i<LINE.length()+1; i++)
	{
		TOKENS_LINE[i] = LINE[i];
	}
  LINE_COUNT++;
  Execute(TOKENS_LINE);
}

void Execute(char TOKENS_LINE[])
{
	bool VALIDATE = false;
  std::string TMP[MAX_BUFFER];
  if (TOKENS_LINE[0] == '$')
  {
    VARIABLE_NUMBER++;
    for (int i = 1; i < BUFFER; i++)
    {
      if (TOKENS_LINE[i] != '=')
      {
        TMP[VARIABLE_NUMBER] += TOKENS_LINE[i];
      }
      else
      {
        i++;
        for (int e=0; e<VARIABLE_NUMBER; e++)
        {
          if (TMP[VARIABLE_NUMBER] == VARIABLE_NAME[e])
          {
            exit(EXIT_FAILURE);
          }
        }
        VARIABLE_NAME[VARIABLE_NUMBER] = TMP[VARIABLE_NUMBER];
        for (i; i < BUFFER; i++)
        {
          if (TOKENS_LINE[i] != ';')
          {
            if ((TOKENS_LINE[i] == '\0') || (TOKENS_LINE[i] == '~'))
            {
              exit(EXIT_FAILURE);
            }
            VARIABLE_VALUE[VARIABLE_NUMBER] += TOKENS_LINE[i];
          }
          else
          {
            break;
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
    for (x; x < BUFFER; x++)
    {
      if (TOKENS_LINE[x] != '=')
      {
        VAR[VARIABLE_NUMBER] += TOKENS_LINE[x];
      }
      else
      {
        break;
      }
    }
    x++;
    for (x; x < BUFFER; x++)
    {
      if (TOKENS_LINE[x] != ';')
      {
        if ((TOKENS_LINE[x] == '\0') || (TOKENS_LINE[x] == '~'))
        {
          exit(EXIT_FAILURE);
        }
        VAR_CONTENT += TOKENS_LINE[x];
      }
      else
      {
        break;
      }
    }
    for (int i= 0; i < MAX_BUFFER; i++)
    {
      if (VARIABLE_NAME[i] == VAR[VARIABLE_NUMBER])
      {
        VALIDATE = true;
        VARIABLE_VALUE[i] = VAR_CONTENT;
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
