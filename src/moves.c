#include "cub3D.h"

void	move_forward(t_game *game, char **map)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.1;
	new_x = game->player.x + game->player.dir_x * move_speed;
	new_y = game->player.y + game->player.dir_y * move_speed;
	if (map[(int)new_y][(int)new_x] == '0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_backward(t_game *game, char **map)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.1;
	new_x = game->player.x - game->player.dir_x * move_speed;
	new_y = game->player.y - game->player.dir_y * move_speed;
	if (map[(int)new_y][(int)new_x] == '0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	strafe_left(t_game *game, char **map)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.1;
	new_x = game->player.x - game->player.plane_x * move_speed;
	new_y = game->player.y - game->player.plane_y * move_speed;
	if (map[(int)new_y][(int)new_x] == '0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	strafe_right(t_game *game, char **map)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.1;
	new_x = game->player.x + game->player.plane_x * move_speed;
	new_y = game->player.y + game->player.plane_y * move_speed;
	if (map[(int)new_y][(int)new_x] == '0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.05;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rot_speed) - 
						game->player.dir_y * sin(-rot_speed);
	game->player.dir_y = old_dir_x * sin(-rot_speed) + 
						game->player.dir_y * cos(-rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rot_speed) - 
						  game->player.plane_y * sin(-rot_speed);
	game->player.plane_y = old_plane_x * sin(-rot_speed) + 
						  game->player.plane_y * cos(-rot_speed);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.05;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed) - 
						game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + 
						game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed) - 
						  game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + 
						  game->player.plane_y * cos(rot_speed);
}