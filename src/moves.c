#include "cub3D.h"

// Función para verificar colisión
int check_collision(char **map, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    
    if (map_x < 0 || map_y < 0 || !map[map_y] || !map[map_y][map_x])
        return (1); // Colisión
    
    return (map[map_y][map_x] == '1');
}

void move_forward(t_game *game, char **map)
{
    double new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
    double new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
    
    if (!check_collision(map, new_x, game->player.y))
        game->player.x = new_x;
    if (!check_collision(map, game->player.x, new_y))
        game->player.y = new_y;
}

void move_backward(t_game *game, char **map)
{
    double new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
    double new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
    
    if (!check_collision(map, new_x, game->player.y))
        game->player.x = new_x;
    if (!check_collision(map, game->player.x, new_y))
        game->player.y = new_y;
}

void strafe_left(t_game *game, char **map)
{
    double new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
    double new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
    
    if (!check_collision(map, new_x, game->player.y))
        game->player.x = new_x;
    if (!check_collision(map, game->player.x, new_y))
        game->player.y = new_y;
}

void strafe_right(t_game *game, char **map)
{
    double new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
    double new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
    
    if (!check_collision(map, new_x, game->player.y))
        game->player.x = new_x;
    if (!check_collision(map, game->player.x, new_y))
        game->player.y = new_y;
}

void rotate_left(t_game *game)
{
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;
    
    game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - 
                         game->player.dir_y * sin(ROT_SPEED);
    game->player.dir_y = old_dir_x * sin(ROT_SPEED) + 
                         game->player.dir_y * cos(ROT_SPEED);
    game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - 
                           game->player.plane_y * sin(ROT_SPEED);
    game->player.plane_y = old_plane_x * sin(ROT_SPEED) + 
                           game->player.plane_y * cos(ROT_SPEED);
}

void rotate_right(t_game *game)
{
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;
    
    game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - 
                         game->player.dir_y * sin(-ROT_SPEED);
    game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + 
                         game->player.dir_y * cos(-ROT_SPEED);
    game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - 
                           game->player.plane_y * sin(-ROT_SPEED);
    game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + 
                           game->player.plane_y * cos(-ROT_SPEED);
}