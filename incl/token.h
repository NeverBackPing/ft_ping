#ifndef TOKEN_H
# define TOKEN_H

#include "ping.h"
#include "hub_struct.h"

typedef enum e_token
{
    OPTION,
    VALUE,
    ADDRESS,
} t_token;

typedef struct s_tokenizer
{
    int token;
    char *data
} t_tokenizer;


#endif
