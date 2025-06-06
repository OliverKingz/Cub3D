/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:35:09 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/06 20:48:13 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_game *game, int dx, int dy, int dang)
{
	t_point new_pos;
	double	angle_rad;

	if (dang != 0)
	{
		game->player.angle += dang * ANGLE_SPEED;
		if (game->player.angle >= 360)
			game->player.angle -= 360;
		else if (game->player.angle < 0)
			game->player.angle += 360;
	}
	new_pos = game->player.pos;
	angle_rad = degrees_to_radians(game->player.angle);
	if (dx != 0 || dy != 0)
	{
		if (dy != 0)
		{
			new_pos.x += cos(angle_rad) * dy * SPEED;
			new_pos.y -= sin(angle_rad) * dy * SPEED;
		}
		if (dx != 0)
		{
			new_pos.x += cos(angle_rad + PI / 2) * dx * SPEED;
			new_pos.y -= sin(angle_rad + PI / 2) * dx * SPEED;
		}
		if (new_pos.x >= 0 && new_pos.x < game->scene.width_map
			&& new_pos.y >= 0 && new_pos.y < game->scene.height_map
			&& game->scene.map2d[(int)new_pos.y][(int)new_pos.x] != '1')
		{
			game->player.pos = new_pos;
			game->player.mmap.x = game->player.pos.x * MAP_TILE;
			game->player.mmap.y = game->player.pos.y * MAP_TILE;
		}
	}
	if (game->is_running == true)
		draw_frame(game);
	printf("P(%f, %f)\n", game->player.pos.x, game->player.pos.y);
}
