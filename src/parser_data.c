#include "cub3D.h"

void	init_data(t_data *data)
{
	data->raw_map = NULL;
	data->no = ft_strdup("X");
	data->so = ft_strdup("X");
	data->we = ft_strdup("X");
	data->ea = ft_strdup("X");
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
    int len;

    len = ft_strlen(argv);
    init_data(&data);
    if (len > 4 && !ft_strcmp(argv + len - 4, ".cub"))
    {
        if (!read_map(argv, &data, game))
        {
            data.error = 1;
            return (data);
        }
    }
    else
    {
        printf("Error:\nNot a .cub file. Use: ./cub3D maps/[map.cub]\n");
        exit(EXIT_FAILURE);
    }
    return (data);
}
