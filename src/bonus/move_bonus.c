/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:35:09 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/15 15:32:15 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	rotate(t_game *game, int dang)
{
	if (dang != 0)
	{
		game->player.angle += dang * ANGLE_SPEED;
		if (game->player.angle >= 360)
			game->player.angle -= 360;
		else if (game->player.angle < 0)
			game->player.angle += 360;
	}
}

void	move(t_game *game, int dx, int dy)
{
	t_point	new_pos;
	double	angle_rad;

	new_pos = game->player.pos;
	angle_rad = deg_to_rad(game->player.angle);
	if (dy != 0)
	{
		new_pos.x += cos(angle_rad) * -dy * SPEED;
		new_pos.y += sin(angle_rad) * -dy * SPEED;
	}
	if (dx != 0)
	{
		new_pos.x += -sin(angle_rad) * dx * SPEED;
		new_pos.y += cos(angle_rad) * dx * SPEED;
	}
	if (new_pos.x >= 0 && new_pos.x < game->scene.width_map
		&& new_pos.y >= 0 && new_pos.y < game->scene.height_map
		&& game->scene.map2d[(int)new_pos.y][(int)new_pos.x] != WALL)
	{
		game->player.pos = new_pos;
		game->player.mmap.x = game->player.pos.x * MMAP_TILE;
		game->player.mmap.y = game->player.pos.y * MMAP_TILE;
	}
}

static void	normalize_move(t_game *game, t_point end_pos)
{
	int	length;

	length = get_distance_length((t_point){0, 0}, end_pos);
	if (length != 0)
	{
		end_pos.x /= length;
		end_pos.y /= length;
	}
	move(game, end_pos.x, end_pos.y);
}

void	update_player_keys_state(t_game *game)
{
	t_point	d;
	int		dang;

	d.x = 0;
	d.y = 0;
	dang = 0;
	if (game->keys.w)
		d.y -= 1;
	if (game->keys.s)
		d.y += 1;
	if (game->keys.a)
		d.x -= 1;
	if (game->keys.d)
		d.x += 1;
	if (game->keys.left)
		dang -= 1;
	if (game->keys.right)
		dang += 1;
	if (d.x != 0 || d.y != 0)
		normalize_move(game, d);
	if (dang != 0)
		rotate(game, dang);
}
