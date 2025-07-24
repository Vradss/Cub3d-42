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

// Teclas (macOS)
# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124

/* double plane_x = 0.0;   // Plano perpendicular a donde miras
double		plane_y = 0.66;  // ← Este número controla el FOV
						// 0.66 = FOV normal (como ojo humano)
						// 1.0 = FOV más amplio
						// 0.5 = FOV más estrecho */
# define FOV 0.66

typedef struct s_player
{
	double x;       // Posición X (continua, no discreta)
	double y;       // Posición Y
	double dir_x;   // Dirección de vista X
	double dir_y;   // Dirección de vista Y
	double plane_x; // Plano de cámara X (para Field of view FOV)
	double plane_y; // Plano de cámara Y
}			t_player;

typedef struct s_map
{
	char **grid;       // ← IGUAL que so_long
	size_t width;      // ← IGUAL que so_long
	size_t height;     // ← IGUAL que so_long
	char *north_tex;   // ← NUEVO: ruta textura norte
	char *south_tex;   // ← NUEVO: ruta textura sur
	char *west_tex;    // ← NUEVO: ruta textura oeste
	char *east_tex;    // ← NUEVO: ruta textura este
	int floor_color;   // ← NUEVO: color suelo RGB
	int ceiling_color; // ← NUEVO: color techo RGB
	char	**map;
}			t_map;

typedef struct s_textures
{
	void *north;     // Imagen textura norte
	void *south;     // Imagen textura sur
	void *west;      // Imagen textura oeste
	void *east;      // Imagen textura este
	int *north_data; // Datos de píxeles norte
	int *south_data; // Datos de píxeles sur
	int *west_data;  // Datos de píxeles oeste
	int *east_data;  // Datos de píxeles este
	int width;       // Ancho texturas
	int height;      // Alto texturas
}			t_textures;

typedef struct s_keys
{
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_m;
	int		key_h;
	int		key_left;
	int		key_right;
	int		key_shift;
	int		key_space;
}			t_keys;

typedef struct s_game
{
	void *mlx;           // ← IGUAL que so_long
	void *win;           // ← IGUAL que so_long
	void *img;           // ← NUEVO: buffer de imagen
	char *img_data;      // ← NUEVO: datos de píxeles
	int bpp;             // ← NUEVO: bits por píxel
	int line_len;        // ← NUEVO: longitud línea
	int endian;          // ← NUEVO: orden bytes
	t_map *map;          // ← Adaptado de so_long
	t_player player;     // ← Adaptado de so_long
	t_textures textures; // ← Nuevo para cub3D
	t_keys	keys;
	int		**zbuffer;
	int		**texture;
}			t_game;

typedef struct s_data
{
	int		reading_pos;
	int		error;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f_color[3];
	int		c_color[3];
	int		map_length;
	size_t	line_size;
	char	**raw_map;
	t_game	*game;
	char	**map;

}			t_data;

typedef struct s_ray
{
	double dir_x;          // Ray direction X component
	double dir_y;          // Ray direction Y component
	int map_x;             // Current X position in map grid
	int map_y;             // Current Y position in map grid
	double delta_dist_x;   // Distance ray travels for 1 X-side unit
	double delta_dist_y;   // Distance ray travels for 1 Y-side unit
	double side_dist_x;    // Distance from current pos to next X-side
	double side_dist_y;    // Distance from current pos to next Y-side
	int step_x;            // Direction to step in X (+1 or -1)
	int step_y;            // Direction to step in Y (+1 or -1)
	int side;              // Wall side hit (0=NS wall, 1=EW wall)
	double perp_wall_dist; // Perpendicular distance to wall
	int line_height;       // Height of wall line to draw
	int draw_start;        // Start pixel for wall line
	int draw_end;          // End pixel for wall line
	double wall_x;         // Exact hit point on wall (0.0 to 1.0)
	int tex_x;             // X coordinate in texture
}			t_ray;

// Functions
char		**read_map_simple(char *filename);
// void find_player(char **map, t_player *player);
void		my_pixel_put(t_game *game, int x, int y, int color);
void		real_raycasting(t_game *game, char **map);

// parsing
t_data	check_data(char *argv, t_game *game);
void		init_data(t_data *data);
int			read_map(char *map, t_data *data, t_game *game);

//parser_textures.c
int	    valid_map_line(char *line, t_data *data);
int     invalid_or_dup_attr(char *line, t_data *data);
int     valid_texture_dir(char *line, t_data *data);
void    update_data_textures(char *file, t_data *data, char nsew);
int     normalize_line(char *line);
int     handle_char(char *line, int *i, int *j, int *space);

//parser_colors.c
int     valid_color(char *line, t_data *data);
int     count_commas(char *line);
char    **split_rgb(char *line, char *linebreak);
int     valid_rgb_params(char **rgb);
void    update_data_colors(char **rgb, t_data *data, char f_or_c);

//parser_map_valid.c
void    map_length(char *line, int fd, char *map, t_data *data);
int     is_only_spaces(char *line);
int     process_map(t_data *data, int fd, t_game *game);
char    *adjust_map_line(char *content, t_data *data);
int     check_n_init_map(t_data *data, int i, t_game *game);
void    get_player_position(char **map, t_game *game);
void    init_pos_player(t_game *game, char **map, int x, int y);
bool    check_player_in_walls(char **map, int size);
bool    exec_check(t_data *data, t_game *game, int i, char **backup_map);
int     check_dup_players(char  letter, char yes_or_no);
int     valid_char_in_map(char *line);

// parser_utils.c
int			file_is_open(char *file);
void		free_array(void **arr);

// Exit & free
void		exit_error(char *info);

// Movement functions
void		move_forward(t_game *game, char **map);
void		move_backward(t_game *game, char **map);
void		strafe_left(t_game *game, char **map);
void		strafe_right(t_game *game, char **map);
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);

// Texture loading functions
int			load_wall_textures(t_game *game, t_data *data);
int			get_texture_pixel(int *texture_data, int x, int y, int tex_width);
int			*get_wall_texture(t_game *game, int side, double ray_dir_x,
				double ray_dir_y);
void		convert_colors_to_int(t_game *game, t_data *data);

#endif