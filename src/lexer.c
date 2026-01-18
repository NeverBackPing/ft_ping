#include "../incl/lexer.h"

bool IsFlag(char *input)
{
    if (!input)
        return (false);
    if (ft_strlen(input) == 2 && input[0] == '-' && ft_isalnum(input[1]))
        return (true);
    return (false);
}

bool IsOption(char* str)
{
    int i = 0;
    const char* keywords[] = { "-v"};
    while (sizeof(keywords) / sizeof(keywords[0]))
    {
        if (ft_strncmp(str, keywords[i], ft_strlen(str)) == 0)
            return true;
    }
    return false;
}