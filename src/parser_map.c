#include "cub3D.h"


/* while loop reads line by line until finding a 1st valid line
with `valid_map_line(line, data)`*/
int     read_map(char *map, t_data *data, t_game *game)
{
    (void)game;
    int     fd;
    char    *line;

    fd = open(map, O_RDONLY);
    if (fd == -1)
        exit_error("Error:\nUnable to open map");
    line = get_next_line(fd);
    while (line != NULL)
    {
        if (valid_map_line(line, data))
            break ;
        data->reading_pos++;
        free(line);
        line = get_next_line(fd);
    }
    //if (line == NULL)
        //exit_error("Error:\nAttributes missing");
    //TODO
    return (close(fd), true);
}