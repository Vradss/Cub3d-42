#include "cub3D.h"

// Función para dibujar línea vertical
void draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
    int y;
    
    y = start;
    while (y <= end)
    {
        if (y >= 0 && y < WIN_HEIGHT)
            my_pixel_put(game, x, y, color);
        y++;
    }
}

void real_raycasting(t_game *game, char **map)
{
    int x;
    
    x = 0;
    while (x < WIN_WIDTH)
    {
        // Calcular dirección del rayo
        double camera_x = 2 * x / (double)WIN_WIDTH - 1;
        double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
        
        // Posición inicial del rayo (jugador)
        int map_x = (int)game->player.x;
        int map_y = (int)game->player.y;
        
        // Distancia que debe recorrer el rayo para ir de un lado X/Y al siguiente
        double delta_dist_x;
        double delta_dist_y;
        
        if (ray_dir_x == 0)
            delta_dist_x = 1e30;
        else
            delta_dist_x = fabs(1 / ray_dir_x);
            
        if (ray_dir_y == 0)
            delta_dist_y = 1e30;
        else
            delta_dist_y = fabs(1 / ray_dir_y);
        
        // Variables para el algoritmo DDA
        double side_dist_x;
        double side_dist_y;
        int step_x;
        int step_y;
        int hit = 0;
        int side; // 0 si es pared NS, 1 si es pared EW
        
        // Calcular step y side_dist inicial
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->player.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
        }
        
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->player.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
        }
        
        // Realizar DDA
        while (hit == 0)
        {
            // Saltar al siguiente lado del mapa, O en dirección x O en dirección y
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            
            // Verificar si el rayo ha golpeado una pared
            if (map[map_y][map_x] == '1')
                hit = 1;
        }
        
        // Calcular distancia proyectada en el plano de la cámara
        double perp_wall_dist;
        
        if (side == 0)
            perp_wall_dist = (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;
        
        // Calcular altura de línea a dibujar en pantalla
        int line_height = (int)(WIN_HEIGHT / perp_wall_dist);
        
        // Calcular punto más alto y más bajo para dibujar en pantalla
        int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
            
        int draw_end = line_height / 2 + WIN_HEIGHT / 2;
        if (draw_end >= WIN_HEIGHT)
            draw_end = WIN_HEIGHT - 1;
        
        // Elegir color de pared
        int color;
        if (side == 1)
            color = 0x00FF0000; // Rojo para paredes EW
        else
            color = 0x0000FF00; // Verde para paredes NS
        
        // Dibujar techo (negro)
        draw_vertical_line(game, x, 0, draw_start - 1, 0x00000000);
        
        // Dibujar pared
        draw_vertical_line(game, x, draw_start, draw_end, color);
        
        // Dibujar suelo (gris)
        draw_vertical_line(game, x, draw_end + 1, WIN_HEIGHT - 1, 0x00808080);
        
        x++;
    }
}