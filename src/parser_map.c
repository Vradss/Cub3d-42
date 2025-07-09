#include "cub3D.h"

int     read_map(char *map, t_data *data, t_game *game)
{
    (void)data;
    (void)game;
    int     fd;
    char    *line;

    fd = open(map, O_RDONLY);
    if (fd == -1)
        exit_error("Error:\nUnable to open map");
    line = get_next_line(fd);
    while (line != NULL)
    {
        //TODO
        data->reading_pos++;
        free(line);
        line = get_next_line(fd);
    }
    //if (line == NULL)
        //exit_error("Error:\nAttributes missing");
    //TODO
    return (close(fd), true);
}