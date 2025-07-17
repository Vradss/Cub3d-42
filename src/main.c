#include "cub3D.h"

// void	my_pixel_put(t_game *game, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
// 		return;
// 	dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
// 	*(unsigned int*)dst = color;
// }

void my_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
    
    // ¿game->img_data es válido?
    if (!game->img_data)
    {
        printf("❌ ERROR: game->img_data es NULL\n");
        return;
    }
    
    dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}
void	render_frame(t_data *data)
{
	real_raycasting(data->game, data->map);
	mlx_put_image_to_window(data->game->mlx, data->game->win,
		data->game->img, 0, 0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		exit(0);
	else if (keycode == W_KEY)
		move_forward(data->game, data->map);
	else if (keycode == S_KEY)
		move_backward(data->game, data->map);
	else if (keycode == A_KEY)
		strafe_left(data->game, data->map);
	else if (keycode == D_KEY)
		strafe_right(data->game, data->map);
	else if (keycode == LEFT_ARROW)
		rotate_left(data->game);
	else if (keycode == RIGHT_ARROW)
		rotate_right(data->game);
	else
		return (0);
	render_frame(data);
	return (0);
}


/*void	init_vars(t_game *game)
{
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->keys.key_w = 0;
	game->keys.key_a = 0;
	game->keys.key_s = 0;
	game->keys.key_d = 0;
	game->keys.key_left = 0;
	game->keys.key_right = 0;
	game->keys.key_shift = 0;
	game->map = malloc(sizeof(t_map));
	if (game->map)
		game->map->grid = NULL;
	game->zbuffer = NULL;
	game->texture = NULL;
}*/

void init_vars(t_game *game)
{
    // Inicializar jugador en valores por defecto
    game->player.x = 0.0;
    game->player.y = 0.0;
    game->player.dir_x = -1.0;
    game->player.dir_y = 0.0;
    game->player.plane_x = 0.0;
    game->player.plane_y = FOV;
    
    // Inicializar mapa
    game->map = malloc(sizeof(t_map));
    if (!game->map)
        exit_error("Error:\nMemory allocation failed");
    game->map->grid = NULL;
    
    // Inicializar otros valores
    game->mlx = NULL;
    game->win = NULL;
    game->img = NULL;
    game->img_data = NULL;
    game->texture = NULL;
    game->zbuffer = NULL;
}

// int	init_mlx(t_game *game)
// {
// 	game->mlx = mlx_init();
// 	if (!game->mlx)
// 	{
// 		printf("Error: MLX init failed\n");
// 		return (1);
// 	}
// 	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D test");
// 	if (!game->win)
// 	{
// 		printf("Error: Window creation failed\n");
// 		return (1);
// 	}
// 	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	game->img_data = mlx_get_data_addr(game->img, &game->bpp, 
// 									 &game->line_len, &game->endian);
// 	return (0);
// }

// En init_mlx, agrega verificaciones:
int init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("❌ ERROR: mlx_init falló\n");
        return (1);
    }
    printf("🔍 DEBUG: mlx_init OK\n");
    
    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D test");
    if (!game->win)
    {
        printf("❌ ERROR: mlx_new_window falló\n");
        return (1);
    }
    printf("🔍 DEBUG: mlx_new_window OK\n");
    
    game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!game->img)
    {
        printf("❌ ERROR: mlx_new_image falló\n");
        return (1);
    }
    printf("🔍 DEBUG: mlx_new_image OK\n");
    
    game->img_data = mlx_get_data_addr(game->img, &game->bpp, 
                                     &game->line_len, &game->endian);
    if (!game->img_data)
    {
        printf("❌ ERROR: mlx_get_data_addr falló\n");
        return (1);
    }
    printf("🔍 DEBUG: mlx_get_data_addr OK\n");
    
    return (0);
}

// int main(int argc, char **argv)
// {
//     t_game game = {0};
// 	t_data data;

//     if (argc != 2)
//     {
//         printf("Error:\nWrong nb of args. Use: ./cub3D maps/[map.cub]\n");
//         exit(EXIT_FAILURE);
//     }
// 	init_vars(&game);
//     // Leer mapa
// 	data = check_data(argv[1], &game);
// 	if (data.error)
// 	{
// 		printf("Error: parsing");
// 		return 1;
// 	}
//     // Init MLX
// 	if (init_mlx(&game) != 0)
// 		return (1);

// 	if (!data.map)
//     {
//         // Fallback: usar read_map_simple si data.map es NULL
// 		printf("Error: Parser didn't create map. Using fallback...\n");
//         data.map = read_map_simple(argv[1]);
//         if (!data.map)
//         {
//             printf("Error: Can't read map\n");
//             return (1);
//         }
//     }
//     // Encontrar jugador
//     find_player(data.map, &game.player);
// 	data.game = &game;
//     render_frame(&data);
//     //mlx_key_hook(game.win, key_hook, &data);
// 	mlx_hook(game.win, 2, 1L<<0, key_hook, &data);
//     mlx_loop(game.mlx);
// 	printf("✅ Llegué al final sin crash\n");
//     return (0);
// }

int main(int argc, char **argv)
{
    t_game game = {0};
    t_data data;

    printf("🔍 DEBUG: Iniciando programa\n");
    
    if (argc != 2)
    {
        printf("Error:\nWrong nb of args. Use: ./cub3D maps/[map.cub]\n");
        exit(EXIT_FAILURE);
    }
    
    printf("🔍 DEBUG: Argumentos OK\n");
    
    init_vars(&game);
    printf("🔍 DEBUG: Variables inicializadas\n");
    
    // Leer mapa
    data = check_data(argv[1], &game);
    printf("🔍 DEBUG: check_data completado, error = %d\n", data.error);
    
    if (data.error)
    {
        printf("Error: parsing");
        return 1;
    }
    
    // Init MLX
    if (init_mlx(&game) != 0)
        return (1);
    printf("🔍 DEBUG: MLX inicializado\n");

    if (!data.map)
    {
        printf("🔍 DEBUG: data.map es NULL, usando fallback\n");
        data.map = read_map_simple(argv[1]);
        if (!data.map)
        {
            printf("Error: Can't read map\n");
            return (1);
        }
        printf("🔍 DEBUG: read_map_simple completado\n");
    }
    else
    {
        printf("🔍 DEBUG: data.map existe\n");
    }
    
    // Verificar que el mapa se cargó correctamente
    printf("🔍 DEBUG: Verificando mapa:\n");
    for (int i = 0; data.map[i]; i++)
    {
        printf("🔍 DEBUG: Línea %d: %s\n", i, data.map[i]);
    }
    
    // Encontrar jugador
    printf("🔍 DEBUG: Buscando jugador...\n");
    find_player(data.map, &game.player);
    printf("🔍 DEBUG: Jugador encontrado en (%.2f, %.2f)\n", game.player.x, game.player.y);
    
    data.game = &game;
    printf("🔍 DEBUG: Antes de render_frame\n");
    
    render_frame(&data);
    printf("🔍 DEBUG: render_frame completado\n");
    
    mlx_hook(game.win, 2, 1L<<0, key_hook, &data);
    printf("🔍 DEBUG: hook configurado, entrando a mlx_loop\n");
    
    mlx_loop(game.mlx);
    printf("✅ Llegué al final sin crash\n");
    return (0);
}

