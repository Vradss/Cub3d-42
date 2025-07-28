/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrads <vrads@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:09:01 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/28 13:02:36 by vrads            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include "../libft/libft.h"
# include "../src/gnl/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define FOV 0.66

#ifdef __APPLE__
    # define ESC_KEY 53
    # define W_KEY 13
    # define A_KEY 0
    # define S_KEY 1
    # define D_KEY 2
    # define LEFT_ARROW 123
    # define RIGHT_ARROW 124
#elif __linux__
    # define ESC_KEY 65307
    # define W_KEY 119
    # define A_KEY 97
    # define S_KEY 115
    # define D_KEY 100
    # define LEFT_ARROW 65361
    # define RIGHT_ARROW 65363
#endif

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_map
{
	char		**grid;
	size_t		width;
	size_t		height;
	char		*north_tex;
	char		*south_tex;
	char		*west_tex;
	char		*east_tex;
	int			floor_color;
	int			ceiling_color;
	char		**map;
}				t_map;

typedef struct s_textures
{
	void		*north;
	void		*south;
	void		*west;
	void		*east;
	int			*north_data;
	int			*south_data;
	int			*west_data;
	int			*east_data;
	int			width;
	int			height;
}				t_textures;

typedef struct s_keys
{
	int			key_a;
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_m;
	int			key_h;
	int			key_left;
	int			key_right;
	int			key_shift;
	int			key_space;
}				t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			bpp;
	int			line_len;
	int			endian;
	t_map		*map;
	t_player	player;
	t_textures	textures;
	t_keys		keys;
	int			**zbuffer;
	int			**texture;
}				t_game;

typedef struct s_data
{
	int			reading_pos;
	int			error;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			f_color[3];
	int			c_color[3];
	int			map_length;
	size_t		line_size;
	char		**raw_map;
	t_game		*game;
	char		**map;

}				t_data;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
}				t_ray;

// Functions
void			my_pixel_put(t_game *game, int x, int y, int color);
void			real_raycasting(t_game *game, char **map);

////// parsing //////

// parser_data.c
t_data			check_data(char *argv, t_game *game);
void			init_data(t_data *data);
int				read_map(char *map, t_data *data, t_game *game);
int				valid_map_line(char *line, t_data *data);

// parser_map.c
int				process_map(t_data *data, int fd, t_game *game);
char			*skip_to_map_start(int fd, int target);
int				read_map_lines(t_data *data, int fd, char *line,
					char **backup_map);
char			*adjust_map_line(char *content, t_data *data);
int				valid_char_in_map(char *line);

// parser_textures.c
int				invalid_or_dup_attr(char *line, t_data *data);
int				valid_texture_dir(char *line, t_data *data);
void			update_data_textures(char *file, t_data *data, char nsew);
int				normalize_line(char *line);
int				handle_char(char *line, int *i, int *j, int *space);

// parser_colors.c
int				valid_color(char *line, t_data *data);
int				count_commas(char *line);
char			**split_rgb(char *line, char *linebreak);
int				valid_rgb_params(char **rgb);
void			update_data_colors(char **rgb, t_data *data, char f_or_c);

// parser_players.c
int				check_dup_players(char letter, char yes_or_no);
bool			check_player_in_walls(char **map, int size);
void			get_player_position(char **map, t_game *game);
void			init_pos_player(t_game *game, char **map, int x, int y);

// parser_map_valid.c
int				check_n_init_map(t_data *data, int i, t_game *game);
bool			exec_check(t_data *data, t_game *game, int i,
					char **backup_map);

// parser_utils.c
int				file_is_open(char *file);
void			map_length(char *line, int fd, char *map, t_data *data);
int				is_only_spaces(char *line);

// Exit & free
void			exit_error(char *info);
void			free_array(void **arr);
int				close_window_hook(t_data *data);
void			cleanup_and_exit(t_data *data);

// Movement functions
void			move_forward(t_game *game, char **map);
void			move_backward(t_game *game, char **map);
void			strafe_left(t_game *game, char **map);
void			strafe_right(t_game *game, char **map);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);

// Texture loading functions
int				load_wall_textures(t_game *game, t_data *data);
int				get_texture_pixel(int *texture_data, int x, int y,
					int tex_width);
int				*get_wall_texture(t_game *game, int side, double ray_dir_x,
					double ray_dir_y);
void			convert_colors_to_int(t_game *game, t_data *data);
void			clear_screen_background(t_game *game);
void			render_textured_wall_line(t_game *game, int x, t_ray *ray);
void			calculate_texture_coordinates(t_game *game, t_ray *ray);

#endif