#include "cub3D.h"

void    map_length(char *line, int fd, char *map, t_data *data)
{
    size_t  length_line;

    while (line != NULL && is_only_spaces(line))
    {
        free(line);
        line = get_next_line(fd);
    }
    while (line != NULL)
    {
        length_line = ft_strlen(line);
        if (length_line > data->line_size)
            data->line_size = length_line;
        data->map_length++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    fd = open(map, O_RDONLY);
}

int is_only_spaces(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\n' && line[i] != '\0')
    {
        if (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\v' || line[i] == '\r'
		|| line[i] == '\n' || line[i] == '\f'))
            return (false);
        i++;
    }
    return (true);
}

static char *skip_to_map_start(int fd, int target)
{
    char    *line;
    int     i;

    i = 0;
    line = get_next_line(fd);
    while (i++ < target)
    {
        free(line);
        line = get_next_line(fd);
    }
    while (line && is_only_spaces(line))
    {
        free(line);
        line = get_next_line(fd);
    }
    return (line);
}
/* Reads the map lines, validates, stores them in data->raw_map and backup_map*/
static int  read_map_lines(t_data *data, int fd, char *line, char **backup_map)
{
    int i;

    i = 0;
    while (line)
    {
        if (!valid_char_in_map(line))
            return (free_array((void **)backup_map), free(line), false);
        backup_map[i] = ft_strdup(line);
        data->raw_map[i++] = adjust_map_line(line, data);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    return (exec_check(data, data->game, i, backup_map)); //TODO
}

char    *adjust_map_line(char *content, t_data *data)
{
    int     i;
    int     content_len;
    char    *line;

    i = -1;
    content_len = data->line_size;
    line = malloc(sizeof(char) * content_len);
    if (line == NULL)
        exit_error("Error:\nMallocation failed");
    while (content[++i] != '\0')
    {
        line[i] = content[i];
        if (content[i] == ' ')
            line[i] = '1';
    }
    while (i < content_len)
    {
        line[i - 1] = '1';
        i++;
    }
    line[content_len -1] = '\0';
    return (line);
}

int check_n_init_map(t_data *data, int i, t_game *game)
{
    int pos;
    int flag;

    pos = 0;
    flag = 0;
    data->raw_map[i] = NULL;
    game->map = malloc(sizeof(t_map));
    if (!game->map)
	    exit_error("Error:\nMalloc failed");
    if (check_dup_players(' ', 'Y'))
        return (false);
    get_player_position(data->raw_map, game); //TODO
    while (data->raw_map[pos])
    {
        if (data->raw_map[pos][0] == '\n')
            flag = 1;
        else if (data->raw_map[pos][0] != '\n'
            && data->raw_map[pos][0] != '\0' && flag)
            exit_error("Error:\nInvalid line inside map");
        pos++;
    }
    game->map->map = data->raw_map;
    return (true);
}

void    get_player_position(char **map, t_game *game)
{
    int y;
    int x;

    y = 0;
    while (map[y] != NULL)
    {
        x = 0;
        while (map[y][x] != '\n' && map[y][x] != '\0')
        {
            if (ft_strchr("NESW", map[y][x]) != NULL)
            {
			    game->player.pos_x = x + 0.5;
			    game->player.pos_y = y + 0.5;
			    game->player.dir_x = 0;
			    game->player.dir_y = -1;
                init_pos_player(game, map, x, y);
                return ;
            }
            x++;
        }
        y++;
    }
}

void    init_pos_player(t_game *game, char **map, int x, int y)
{
    char    pos;

    pos = map[y][x];
    if (pos == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
    else if (pos == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
    else if (pos == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
    else if (pos == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
	game->player.plane_x = game->player.dir_y * 0.66;
	game->player.plane_y = -game->player.dir_x * 0.66;
}

static bool	check_all_closed(int x, int y, char **map, int size)
{
	bool	is_closed;

	if (y < 0 || y >= size || x < 0 || x >= (int)ft_strlen(map[y]))
		return (false);
	if (map[y][x] == '1' || map[y][x] == ' ')
		return (true);
	map[y][x] = '1';
	is_closed = true;
	is_closed &= check_all_closed(x, y - 1, map, size);
	is_closed &= check_all_closed(x, y + 1, map, size);
	is_closed &= check_all_closed(x - 1, y, map, size);
	is_closed &= check_all_closed(x + 1, y, map, size);
	return (is_closed);
}

bool	check_player_in_walls(char **map, int size)
{
	int	player[2];
	int	x_y[2];

	player[0] = -1;
	player[1] = -1;
	x_y[0] = 0;
	x_y[1] = 0;
	while (x_y[0] < size && player[0] == -1)
	{
		x_y[1] = 0;
		while (x_y[1] < (int)ft_strlen(map[x_y[0]]) && player[0] == -1)
		{
			if (map[x_y[0]][x_y[1]] == 'S' || map[x_y[0]][x_y[1]] == 'N' ||
				map[x_y[0]][x_y[1]] == 'E' || map[x_y[0]][x_y[1]] == 'W')
			{
				player[0] = x_y[1];
				player[1] = x_y[0];
			}
			x_y[1]++;
		}
		x_y[0]++;
	}
	if (player[0] == -1)
		return (false);
	return (check_all_closed(player[0], player[1], map, size));
}

bool    exec_check(t_data *data, t_game *game, int i, char **backup_map)
{
    int pos;

    backup_map[i] = NULL;
    pos = 0;
    while (backup_map[pos])
    {
        if (ft_strlen(backup_map[pos]) > 40 || pos >= 20)
            return (free_array((void **)backup_map), false);
        pos++;
    }
    if (!check_n_init_map(data, i, game))
        return (free_array((void **)backup_map), false);
    if (!check_player_in_walls(backup_map, data->map_length))
        return (free_array((void **)backup_map), false);
    if (backup_map[i - 1][0] == '\0' || backup_map[i - 1][0] == '\n')
        return (free_array((void **)backup_map), false);
    free_array((void **)backup_map);
    return (true);
}

int process_map(t_data *data, int fd, t_game *game)
{
    char    *line;
    char    **backup_map;

    data->game = game;
    line = skip_to_map_start(fd, data->reading_pos);
    data->raw_map = ft_calloc(data->map_length + 1, sizeof(char *));
    backup_map = ft_calloc(data->map_length + 1, sizeof(char *));
    if (!data->raw_map || !backup_map)
        exit_error("Error:\nMallocation failed");
    if (!line)
        return (free_array((void **)backup_map), close(fd), false);
    if (!read_map_lines(data, fd, line, backup_map))
        return (close(fd), false);
    return (close(fd), true);
}
int check_dup_players(char  letter, char yes_or_no)
{
    static int  n = 0;
    static int  s = 0;
    static int  e = 0;
    static int  w = 0;
    int         sum;

    if (letter == 'N')
        n++;
    else if (letter == 'S')
        s++;
    else if (letter == 'E')
        e++;
    else if (letter == 'W')
        w++;
    if (n > 1 || s > 1 || e > 1 || w > 1)
        exit_error("Error:\nDuplicated player");
    if (yes_or_no == 'Y')
    {
        sum = n + s + e + w;
        if (sum == 0)
            exit_error("Error:\nNo player found");
        if (sum > 1)
            exit_error("Error:\nMultiple players not allowed");
    }
    return (false);
}

int valid_char_in_map(char *line)
{
    int     i;
    char    letter;

    i = 0;
    if (line[i] == '\n' || line[i] == '\0')
        return (false);
    while (line[i] != '\n' && line[i] != '\0')
    {
        letter = line[i];
        if (letter == ' ' || letter == '0' || letter == '1' ||
            letter == 'N' || letter == 'S' || letter == 'E' ||
            letter == 'W')
            {
                if (check_dup_players(letter, 'N'))
                    return (false);
                i++;
            }
            else if (letter == '\0')
                return (true);
            else
                exit_error("Error\nInvalid caracter");
    }
    return (true);
}