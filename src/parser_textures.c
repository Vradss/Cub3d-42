#include "cub3D.h"

int	valid_map_line(char *line, t_data *data)
{
	if (ft_strcmp(data->no, "X") && ft_strcmp(data->so, "X")
		&& ft_strcmp(data->we, "X") && ft_strcmp(data->ea, "X")
		&& data->f_color[0] != -1 && data->c_color[0] != -1)
		return (true);
    invalid_or_dup_attr(line, data);
    if (ft_strncmp(line, "NO ", 3) == 0
        || ft_strncmp(line, "SO ", 3) == 0
        || ft_strncmp(line, "EA ", 3) == 0
        || ft_strncmp(line, "WE ", 3) == 0)
        if (!valid_texture_dir(line, data))
            return (false);
	if ((ft_strncmp(line, "F ", 2) == 0) || (ft_strncmp(line, "C ", 2) == 0))
	{
		if (!valid_color(line, data))
			return (false);
	}
	else
        return (false);
    return (false);
}

int invalid_or_dup_attr(char *line, t_data *data)
{
    if (line[0] != '\n' && ft_strncmp(line, "NO", 2) != 0
        && ft_strncmp(line, "SO", 2) != 0
        && ft_strncmp(line, "EA", 2) != 0
        && ft_strncmp(line, "WE", 2) != 0
        && ft_strncmp(line, "F", 1) != 0
        && ft_strncmp(line, "C", 1) != 0)
        exit_error("Error:\nIncorrect attributes");
    if (ft_strncmp(line, "NO ", 3) == 0 && ft_strcmp(data->no, "X") != 0)
        exit_error("Error:\n'NO' parameter duplicated");
    if (ft_strncmp(line, "SO ", 3) == 0 && ft_strcmp(data->so, "X") != 0)
        exit_error("Error:\n'SO' parameter duplicated");
    if (ft_strncmp(line, "EA ", 3) == 0 && ft_strcmp(data->ea, "X") != 0)
        exit_error("Error:\n'EA' parameter duplicated");
    if (ft_strncmp(line, "WE ", 3) == 0 && ft_strcmp(data->we, "X") != 0)
        exit_error("Error:\n'WE' parameter duplicated");
    if (ft_strncmp(line, "F ", 2) == 0 && data->f_color[0] != -1)
        exit_error("Error:\n'F' parameter duplicated");
    if (ft_strncmp(line, "C ", 2) == 0 && data->c_color[0] != -1)
        exit_error("Error:\n'C' parameter duplicated");
    return (false);
}

int valid_texture_dir(char *line, t_data *data)
{
    char    *file;
    char    nsew;

    if (ft_strncmp(line, "NO ", 3) == 0)
        nsew = 'N';
    else if (ft_strncmp(line, "SO ", 3) == 0)
        nsew = 'S';
    else if (ft_strncmp(line, "EA ", 3) == 0)
        nsew = 'E';
    else if (ft_strncmp(line, "WE ", 3) == 0)
        nsew = 'W';
    else
        return (false);
    file = ft_strtrim(line + 2, " \n");
    if (!file)
        return (false);
    if (file_is_open(file))
        update_data_textures(file, data, nsew);
    else
        return (free(file), false);
    return (true);
}

void    update_data_textures(char *file, t_data *data, char nsew)
{
    if (nsew == 'N')
    {
        free(data->no);
        data->no = ft_strdup(file);
    }
    if (nsew == 'S')
    {
        free(data->so);
        data->so = ft_strdup(file);
    }
    if (nsew == 'E')
    {
        free(data->ea);
        data->ea = ft_strdup(file);
    }
    if (nsew == 'W')
    {
        free(data->we);
        data->we = ft_strdup(file);
    }
    free(file);
}