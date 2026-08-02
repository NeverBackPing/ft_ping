#include "../dep/libft/libft.h"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        ft_putstr_fd("sudo ./ft_ping [OPTION] <adresse>\n", 2);
        return (0);
    }

    (void)av;
    
    return (0);
}