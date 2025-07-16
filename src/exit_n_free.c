#include "cub3D.h"

void    exit_error(char *info)
{
    ft_putstr_fd(info, 2);
    ft_putstr_fd("\n", 2);
    exit(EXIT_FAILURE);
}