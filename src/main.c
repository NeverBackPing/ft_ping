#include "../incl/ping.h"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        ft_putstr_fd("sudo ./ft_ping [OPTION] <adresse>\n", 2);
        return (0);
    }

    t_tokenizer *tokenizer;
    
    tokenizer = NULL;
    token_input(&tokenizer, av, ac);

    t_client client_;

    check_input(&client_, av, ac);

    return (0);
}