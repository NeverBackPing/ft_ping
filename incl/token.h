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
    char *data;

    struct t_tokenizer* next;
    struct t_tokenizer* prev;
} t_tokenizer;

void			insertAtBeginning(t_tokenizer *head, int token, char *data);
void			data_clear(t_tokenizer **lst);
void			printListForward(t_tokenizer* head);
void			token_input(t_tokenizer **tokenizer, char **input, int nbr_input);

#endif
