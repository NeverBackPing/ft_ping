#include "../incl/lexer.h"

bool IsFlag(char *input)
{
    return (input[0] == '-');
}


bool IsOption(char* str)
{
    int i = 0;
    const char* keywords[] = { "-v"};
    while (sizeof(keywords) / sizeof(keywords[0]))
    {
        if (ft_strcmp(str, keywords[i]) == 0)
            return true;
    }
    return false;
}