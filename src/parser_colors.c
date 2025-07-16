#include "cub3D.h"

int valid_color(char *line, t_data *data)
{
    char    **rgb;

    if (!count_commas(line))
        exit_error("Error:\nMust be 3 colors separated by 2 commas");
    rgb = split_rgb(line, " \n");
    valid_rgb_params(rgb);
    update_data_colors(rgb, data, line[0]);
    return (true);
}

int count_commas(char *line)
{
    int i;
    int nb_of_comas;

    i = 0;
    nb_of_comas = 0;
    while (line[i] != '\0')
    {
        if (line[i] == ',')
            nb_of_comas++;
        i++;
    }
    if (nb_of_comas != 2)
        return (false);
    return (true);
}

char    **split_rgb(char *line, char *linebreak)
{
    char    *trimmed_line;
    char    **rgb;

    trimmed_line = ft_strtrim(line + 1, linebreak);
    if (!trimmed_line)
        exit_error("Error:\nMemory allocation failed for color parsing");
    rgb = ft_split(trimmed_line, ',');
    free (trimmed_line);
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
        exit_error("Missing RGB parameter(s)");
    return (rgb);
}

int valid_rgb_params(char **rgb)
{
    int     i;
    int     value;
    char    *str;

    //NECESSARY??
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		exit_error("Error:\nRGB must have exactly 3 values");
    i = 0;
    while (i < 3)
    {
        str = rgb[i];
        while (*str)
        {
            if (!ft_isdigit(*str))
                exit_error("Error:\nInvalid character(s) for RGB line");
            str++;
        }
        value = ft_atoi(rgb[i]);
        if (value < 0 || value > 255)
            exit_error("Error:\nRGB value out of range");
        i++;
    }
    return (true);
}

void    update_data_colors(char **rgb, t_data *data, char f_or_c)
{
    if (f_or_c == 'F')
    {
        data->f_color[0] = ft_atoi(rgb[0]);
        data->f_color[1] = ft_atoi(rgb[1]);
        data->f_color[2] = ft_atoi(rgb[2]);
    }
    else if (f_or_c == 'C')
    {
        data->c_color[0] = ft_atoi(rgb[0]);
        data->c_color[1] = ft_atoi(rgb[1]);
        data->c_color[2] = ft_atoi(rgb[2]);
    }
    free_array((void **)rgb);
}