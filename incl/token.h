#ifndef TOKEN_H
# define TOKEN_H

#include "ping.h"
#include "lexer.h"
#include "hub_struct.h"

typedef enum e_token
{
    OPTION,
    VALUE,
} t_token;

typedef struct s_tokenizer
{
    int token;
    char *data;

    struct s_tokenizer *next;
    struct s_tokenizer *prev;
} t_tokenizer;

void			insertAtBeginning(t_tokenizer **tokenizer, t_tokenizer *new_node);
void	        data_clear(t_tokenizer **tokenizer);
void			printListForward(t_tokenizer* head);
void			token_input(t_tokenizer **tokenizer, char **input, int nbr_input);

#endif
