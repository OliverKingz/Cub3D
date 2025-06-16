/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:13:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/16 15:22:46 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	close_hook(void *param)
{
	t_game	*game;

	game = param;
	free_game(game);
	if (game->is_running)
		game->is_running = false;
	if (DEBUG_MODE)
		printf("\nGame closed successfully.\n");
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	bool	pressed;

	game = (t_game *)param;
	pressed = (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT);
	if (keydata.key == MLX_KEY_ESCAPE && pressed)
		close_hook(game);
	if (keydata.key == MLX_KEY_W)
		game->keys.w = pressed;
	if (keydata.key == MLX_KEY_S)
		game->keys.s = pressed;
	if (keydata.key == MLX_KEY_A)
		game->keys.a = pressed;
	if (keydata.key == MLX_KEY_D)
		game->keys.d = pressed;
	if (keydata.key == MLX_KEY_E)
		game->keys.e = keydata.action == MLX_PRESS;
}

void	open_close_door(t_game *game, t_dir dir)
{
	int	x;
	int	y;

	x = (int)game->player.pos.x;
	y = (int)game->player.pos.y;
	if (dir == NORTH)
		y -= 1;
	else if (dir == SOUTH)
		y += 1;
	else if (dir == EAST)
		x += 1;
	else if (dir == WEST)
		x -= 1;
	if (game->scene.map2d[y][x] == DOOR_OPEN)
		game->scene.map2d[y][x] = DOOR_CLOSED;
	else if(game->scene.map2d[y][x] == DOOR_CLOSED)
		game->scene.map2d[y][x] = DOOR_OPEN;
	draw_frame(game);
	game->keys.e = false;
}

void	key_door(t_game *game)
{
	if (310 >= game->player.angle && game->player.angle >= 230)
		open_close_door(game, NORTH);
	else if (130 >= game->player.angle && game->player.angle >= 50)
		open_close_door(game, SOUTH);
	else if ((40 >= game->player.angle && game->player.angle >= 0)
				|| (360 > game->player.angle && game->player.angle >= 320))
		open_close_door(game, EAST);
	else if (220 >= game->player.angle && game->player.angle >= 140)
		open_close_door(game, WEST);
}

void	loop_hook(void *param)
{
	t_game	*game;
	t_point	prev_pos;
	double	prev_angle;

	game = (t_game *)param;
	prev_pos.x = game->player.pos.x;
	prev_pos.y = game->player.pos.y;
	prev_angle = game->player.angle;
	if (USE_MOUSE)
		update_player_state(game);
	else
		update_player_keys_state(game);
	if (game->keys.e)
		key_door(game);
	if (game->player.pos.x != prev_pos.x || game->player.pos.y != prev_pos.y
		|| game->player.angle != prev_angle)
	{
		draw_frame(game);
		prev_pos.x = game->player.pos.x;
		prev_pos.y = game->player.pos.y;
		prev_angle = game->player.angle;
	}
	if (DEBUG_MODE)
		fps_counter(game);
}

void	fps_counter(t_game *game)
{
	static int		frame_count = 0;
	static double	last_time = 0.0;
	double			current_time;
	double			delta_time;

	current_time = mlx_get_time();
	delta_time = current_time - last_time;
	if (delta_time >= 1.0)
	{
		printf("FPS: %d | ", frame_count);
		printf("P(%f, %f, %f)\n", game->player.pos.x, game->player.pos.y,
			game->player.angle);
		frame_count = 0;
		last_time = current_time;
	}
	frame_count++;
}
