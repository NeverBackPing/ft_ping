#ifndef LEXER_H
# define LEXER_H

#include "ping.h"


bool IsOption(char *input);
bool IsFlag(char *input);
bool lexing(t_tokenizer *tokenizer, t_client *client_);


#endif
