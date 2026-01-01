#include "../incl/ping.h"

int main(int ac, char **av)
{
    (void) av;
    if (ac != 2 && ac != 3)
    {
        ft_putstr_fd("sudo ./ft_ping [OPTION] <adresse>", 2);
        return (0);
    }
    return (ac);
}