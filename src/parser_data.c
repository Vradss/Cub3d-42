#include "cub3D.h"

void	init_data(t_data *data)
{
	data->raw_map = NULL;
	data->no = strdup("X"); //CHANGE TO FT_STRDUP
	data->so = strdup("X");
	data->we = strdup("X");
	data->ea = strdup("X");
	data->f_color[0] = -1;
	data->f_color[1] = -1;
	data->f_color[2] = -1;
	data->c_color[0] = -1;
	data->c_color[1] = -1;
	data->c_color[2] = -1;
	data->reading_pos = 0;
	data->map_length = 0;
	data->line_size = 0;
	data->error = 0;
}

t_data check_data(char *argv, t_game *game)
{
    t_data data;

    (void)argv;
    (void)game;

    init_data(&data);
    
    printf("ta race\n");
    return (data);
}