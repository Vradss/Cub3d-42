#include "cub3D.h"

void    my_pixel_put(t_game *game, int x, int y, int color)
{
    char    *dst;
    
    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
    dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

int key_hook(int keycode, t_game *game)
{
    printf("Tecla presionada: %d\n", keycode);
    
    if (keycode == ESC_KEY)
        exit(0);
    else if (keycode == W_KEY)
    {
        game->player.x += 0.1;
        printf("Moviendo a: (%.1f, %.1f)\n", game->player.x, game->player.y);
    }
    
    return (0);
}

void	init_vars(t_game *game)
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
	game->map->grid = NULL; // CHECK THIS
	game->zbuffer = NULL;
	game->texture = NULL;
}

int main(int argc, char **argv)
{
    t_game game;
	t_data data;

    if (argc == 2)
    {
        // init MLX
        // init vars
        data = check_data(argv[1], &game);
        printf("NO texture: %s\n", data.no);
        // go to game: game_main(&game, &data);
    }
    else
    {
        printf("Error:\nWrong nb of args. Use: ./cub3D maps/[map.cub]\n");
        exit(EXIT_FAILURE);
    }
    
    // Leer mapa
    char **map = read_map_simple(argv[1]);
    if (!map)
    {
        printf("Error: Can't read map\n");
        return (1);
    }
    
    // Encontrar jugador
    find_player(map, &game.player);
        
    // Init MLX
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        printf("Error: MLX init failed\n");
        return (1);
    }
    
    game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D test");
    if (!game.win)
    {
        printf("Error: Window creation failed\n");
        return (1);
    }
    
    // Crear buffer de imagen
    game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
    game.img_data = mlx_get_data_addr(game.img, &game.bpp, &game.line_len, &game.endian);
    
    printf("Buffer creado: %d bpp, %d line_len\n", game.bpp, game.line_len);
    
    
    real_raycasting(&game, map);
    mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
    
    mlx_key_hook(game.win, key_hook, &game);
    
    printf("✅ Todo listo, iniciando loop\n");
    mlx_loop(game.mlx);
    
    return (0);
}