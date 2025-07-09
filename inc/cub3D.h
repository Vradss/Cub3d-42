#ifndef CUB3D
# define CUB3D

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "../src/gnl/get_next_line.h"
# include "../libft/libft.h"
# include <string.h>
# include <stdbool.h>


/* 
Esta era mi estructura de so_long, eran int porque eran casillas especificias
64x64px, ahora en la nueva struct tiene que ser double porque es continuo, posicion
del jugador puede ser 1.654743
typedef struct s_vec2
{
	int	x;
	int	y;
}				t_vec2;

typedef struct s_player
{
	t_vec2		pos;
}				t_player; */


#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Teclas (macOS)
# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1  
# define D_KEY 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124

/* double plane_x = 0.0;   // Plano perpendicular a donde miras
double plane_y = 0.66;  // ← Este número controla el FOV
                        // 0.66 = FOV normal (como ojo humano)
                        // 1.0 = FOV más amplio
                        // 0.5 = FOV más estrecho */
#define FOV 0.66

typedef struct s_player
{
    double  x;          // Posición X (continua, no discreta)
    double  y;          // Posición Y  
    double  dir_x;      // Dirección de vista X
    double  dir_y;      // Dirección de vista Y
    double  plane_x;    // Plano de cámara X (para Field of view FOV)
    double  plane_y;    // Plano de cámara Y
}   t_player;


typedef struct s_map
{
    char    **grid;         // ← IGUAL que so_long
    size_t  width;          // ← IGUAL que so_long  
    size_t  height;         // ← IGUAL que so_long
    char    *north_tex;     // ← NUEVO: ruta textura norte
    char    *south_tex;     // ← NUEVO: ruta textura sur
    char    *west_tex;      // ← NUEVO: ruta textura oeste  
    char    *east_tex;      // ← NUEVO: ruta textura este
    int     floor_color;    // ← NUEVO: color suelo RGB
    int     ceiling_color;  // ← NUEVO: color techo RGB
}   t_map;

typedef struct s_textures
{
    void    *north;         // Imagen textura norte
    void    *south;         // Imagen textura sur
    void    *west;          // Imagen textura oeste
    void    *east;          // Imagen textura este
    int     *north_data;    // Datos de píxeles norte
    int     *south_data;    // Datos de píxeles sur
    int     *west_data;     // Datos de píxeles oeste
    int     *east_data;     // Datos de píxeles este
    int     width;          // Ancho texturas
    int     height;         // Alto texturas
}   t_textures;

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
    void        *mlx;       // ← IGUAL que so_long
    void        *win;       // ← IGUAL que so_long
    void        *img;       // ← NUEVO: buffer de imagen
    char        *img_data;  // ← NUEVO: datos de píxeles
    int         bpp;        // ← NUEVO: bits por píxel
    int         line_len;   // ← NUEVO: longitud línea
    int         endian;     // ← NUEVO: orden bytes
    t_map       *map;       // ← Adaptado de so_long
    t_player    player;     // ← Adaptado de so_long  
    t_textures  textures;   // ← Nuevo para cub3D
    t_keys		keys;
    int			**zbuffer;
	int			**texture;
}   t_game;

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
}				t_data;



// Functions
char **read_map_simple(char *filename);
void find_player(char **map, t_player *player);
void my_pixel_put(t_game *game, int x, int y, int color);
void real_raycasting(t_game *game, char **map);

// parsing
t_data check_data(char *argv, t_game *game);
void	init_data(t_data *data);
int     read_map(char *map, t_data *data, t_game *game);

//Exit & free
void    exit_error(char *info);


#endif