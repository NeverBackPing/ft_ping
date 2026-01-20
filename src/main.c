#include "../incl/ping.h"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        ft_putstr_fd("sudo ./ft_ping [OPTION] <adresse>\n", 2);
        return (0);
    }

    t_tokenizer *tokenizer = NULL;

    token_input(&tokenizer, av, ac);

    t_client *client_ = NULL;

    if (lexing(&tokenizer, &client_))
        return (0);

    check_input(&client_, av, ac);

    data_clear(&tokenizer);
    data_clear(&client_->ping);
    data_clear(&client_);
    return (0);
}