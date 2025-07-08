
#include <cub3D.h>

void real_raycasting(t_game *game, char **map)
{
    for (int x = 0; x < WIN_WIDTH; x++)
    {
        // Calcular dirección del rayo para esta columna
        double camera_x = 2 * x / (double)WIN_WIDTH - 1; // -1 a 1
        double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
        
        // Posición actual en el mapa
        int map_x = (int)game->player.x;
        int map_y = (int)game->player.y;
        

        
        // DDA simple para encontrar pared
        while (map[map_y][map_x] == '0') // Mientras no haya pared
        {
            if (ray_dir_x < 0) map_x--;
            else map_x++;
            if (ray_dir_y < 0) map_y--;  
            else map_y++;
        }
        
        // Calcular distancia aproximada (simplificado)
        double distance = sqrt(pow(map_x - game->player.x, 2) + pow(map_y - game->player.y, 2));
        
        // Altura de la línea en pantalla
        int line_height = (int)(WIN_HEIGHT / distance);
        int draw_start = (-line_height / 2) + (WIN_HEIGHT / 2);
        int draw_end = (line_height / 2) + (WIN_HEIGHT / 2);
        
        // Dibujar línea vertical
        for (int y = draw_start; y < draw_end; y++)
        {
            if (y >= 0 && y < WIN_HEIGHT)
                my_pixel_put(game, x, y, 0xFFFFFF); // Blanco = pared
        }
    }
    
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}