#include "cub3D.h"

int file_is_open(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        exit_error("Error:\nImpossible to open file");
        return (false);
    }
    close (fd);
    return (true);
}

void    free_array(void **arr)
{
    int i;
    if (arr == NULL)
        return ;
    i = -1;
    while (arr[++i] != NULL)
        free(arr[i]);
    free(arr);
}